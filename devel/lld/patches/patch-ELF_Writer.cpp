$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: R_MIPS_LITERAL, R_MIPS_PJUMP, and .sbss before .bss
- lld: _ftext, _fdata and _fbss, as IRIX's ld defines them

--- ELF/Writer.cpp.orig
+++ ELF/Writer.cpp
@@ -258,6 +258,11 @@
   ctx.sym.etext2 = add("_etext", -1);
   ctx.sym.edata1 = add("edata", -1);
   ctx.sym.edata2 = add("_edata", -1);
+  if (ctx.arg.osabi == ELFOSABI_IRIX) {
+    ctx.sym.ftext = add("_ftext", -1);
+    ctx.sym.fdata = add("_fdata", -1);
+    ctx.sym.fbss = add("_fbss", -1);
+  }
 }
 
 static void demoteDefined(Defined &sym, DenseMap<SectionBase *, size_t> &map) {
@@ -777,6 +782,12 @@
     // because data in these sections is addressable with a gp relative address.
     if (osec.flags & SHF_MIPS_GPREL)
       rank |= 2;
+    // IRIX: .sbss goes before .bss, as SGI's ld (and GNU ld) put it, so it
+    // stays next to the other gp-relative sections; after a large .bss it is
+    // out of $gp's reach. SGI's objects use .sbss freely.
+    if (ctx.arg.osabi == ELFOSABI_IRIX && osec.type == SHT_NOBITS &&
+        !(osec.flags & SHF_MIPS_GPREL))
+      rank |= 4;
   }
 
   if (ctx.arg.emachine == EM_RISCV) {
@@ -907,6 +918,29 @@
       ctx.sym.end2->section = last->lastSec;
   }
 
+  // IRIX: _ftext is the start of the first executable section, _fdata of the
+  // first writable one with contents, _fbss of the first uninitialized one.
+  if (ctx.sym.ftext || ctx.sym.fdata || ctx.sym.fbss) {
+    OutputSection *ftext = nullptr, *fdata = nullptr, *fbss = nullptr;
+    for (OutputSection *os : ctx.outputSections) {
+      if (!(os->flags & SHF_ALLOC) || (os->flags & SHF_TLS))
+        continue;
+      if (!ftext && (os->flags & SHF_EXECINSTR))
+        ftext = os;
+      if (!fdata && (os->flags & SHF_WRITE) && os->type != SHT_NOBITS)
+        fdata = os;
+      if (!fbss && os->type == SHT_NOBITS)
+        fbss = os;
+    }
+    for (auto [sym, os] : {std::pair(ctx.sym.ftext, ftext),
+                           std::pair(ctx.sym.fdata, fdata),
+                           std::pair(ctx.sym.fbss, fbss)})
+      if (sym && os) {
+        sym->section = os;
+        sym->value = 0;
+      }
+  }
+
   if (ctx.sym.bss) {
     // On RISC-V, set __bss_start to the start of .sbss if present.
     OutputSection *sbss =
@@ -1936,6 +1970,17 @@
         for (Symbol *sym : file->requiredSymbols) {
           if (sym->dsoDefined)
             continue;
+          // STO_MIPS_OPTIONAL: the reference may go unresolved, like a
+          // weak one. IRIX libraries use it.
+          if (ctx.arg.emachine == EM_MIPS &&
+              (sym->stOther & STO_MIPS_OPTIONAL))
+            continue;
+          // Provided at run time by rld (libc) and by the OpenGL runtime
+          // (libGLcore), never by an object at link time.
+          if (ctx.arg.osabi == ELFOSABI_IRIX &&
+              (sym->getName() == "_rld_new_interface" ||
+               sym->getName() == "gl_INTERPRET_END"))
+            continue;
           if (sym->isUndefined() && !sym->isWeak()) {
             ELFSyncStream(ctx, diag)
                 << "undefined reference: " << sym << "\n>>> referenced by "
@@ -2010,6 +2055,18 @@
         osec->shName = ctx.in.shStrTab->addString(osec->name);
     }
 
+  // IRIX: a section symbol in .dynsym for each allocated output section, for
+  // dynamic relocations that would otherwise name no symbol, which rld
+  // ignores (see DynamicReloc::computeRawIRIX). rld needs them named to tell
+  // them apart.
+  if (ctx.arg.osabi == ELFOSABI_IRIX && ctx.mainPart->dynSymTab)
+    for (OutputSection *osec : ctx.outputSections)
+      if ((osec->flags & SHF_ALLOC) && osec->partition == 1)
+        ctx.mainPart->dynSymTab->addSymbol(
+            makeDefined(ctx, ctx.internalFile, osec->name, STB_LOCAL,
+                        /*stOther=*/0, STT_SECTION, /*value=*/0,
+                        /*size=*/0, osec));
+
   // Prefer command line supplied address over other constraints.
   for (OutputSection *sec : ctx.outputSections) {
     auto i = ctx.arg.sectionStartMap.find(sec->name);
@@ -2047,9 +2104,17 @@
       }
       if (ctx.arg.emachine == EM_MIPS) {
         // Add separate segments for MIPS-specific sections.
-        addPhdrForSection(part, SHT_MIPS_REGINFO, PT_MIPS_REGINFO, PF_R);
-        addPhdrForSection(part, SHT_MIPS_OPTIONS, PT_MIPS_OPTIONS, PF_R);
-        addPhdrForSection(part, SHT_MIPS_ABIFLAGS, PT_MIPS_ABIFLAGS, PF_R);
+        // On IRIX each lands third, so add them in reverse to end up
+        // OPTIONS, REGINFO, ABIFLAGS, as MIPSpro's are.
+        if (ctx.arg.osabi == ELFOSABI_IRIX) {
+          addPhdrForSection(part, SHT_MIPS_ABIFLAGS, PT_MIPS_ABIFLAGS, PF_R);
+          addPhdrForSection(part, SHT_MIPS_REGINFO, PT_MIPS_REGINFO, PF_R);
+          addPhdrForSection(part, SHT_MIPS_OPTIONS, PT_MIPS_OPTIONS, PF_R);
+        } else {
+          addPhdrForSection(part, SHT_MIPS_REGINFO, PT_MIPS_REGINFO, PF_R);
+          addPhdrForSection(part, SHT_MIPS_OPTIONS, PT_MIPS_OPTIONS, PF_R);
+          addPhdrForSection(part, SHT_MIPS_ABIFLAGS, PT_MIPS_ABIFLAGS, PF_R);
+        }
       }
       if (ctx.arg.emachine == EM_RISCV)
         addPhdrForSection(part, SHT_RISCV_ATTRIBUTES, PT_RISCV_ATTRIBUTES,
@@ -2316,8 +2381,10 @@
   unsigned partNo = part.getNumber(ctx);
   bool isMain = partNo == 1;
 
-  // Add the first PT_LOAD segment for regular output sections.
-  uint64_t flags = computeFlags(ctx, PF_R);
+  // Add the first PT_LOAD segment for regular output sections. On IRIX it
+  // also holds the text, as MIPSpro's first segment does.
+  uint64_t flags = computeFlags(
+      ctx, ctx.arg.osabi == ELFOSABI_IRIX ? PF_R | PF_X : PF_R);
   PhdrEntry *load = nullptr;
 
   // nmagic or omagic output does not have PT_PHDR, PT_INTERP, or the readonly
@@ -2439,8 +2506,18 @@
     ret.push_back(std::move(tlsHdr));
 
   // Add an entry for .dynamic.
-  if (OutputSection *sec = part.dynamic->getParent())
-    addHdr(PT_DYNAMIC, sec->getPhdrFlags())->add(sec);
+  if (OutputSection *sec = part.dynamic->getParent()) {
+    if (ctx.arg.osabi == ELFOSABI_IRIX && ret.size() >= 2) {
+      // rld wants the dynamic segment (and the MIPS ones, which
+      // addPhdrForSection puts before it) ahead of the loadable ones.
+      ret.insert(ret.begin() + 2,
+                 std::make_unique<PhdrEntry>(ctx, PT_DYNAMIC,
+                                             sec->getPhdrFlags()));
+      ret[2]->add(sec);
+    } else {
+      addHdr(PT_DYNAMIC, sec->getPhdrFlags())->add(sec);
+    }
+  }
 
   if (relRo->firstSec)
     ret.push_back(std::move(relRo));
@@ -2523,7 +2600,11 @@
 
   auto entry = std::make_unique<PhdrEntry>(ctx, pType, pFlags);
   entry->add(*i);
-  part.phdrs.push_back(std::move(entry));
+  // IRIX: third, ahead of PT_DYNAMIC and the loadable segments.
+  if (ctx.arg.osabi == ELFOSABI_IRIX && part.phdrs.size() >= 2)
+    part.phdrs.insert(part.phdrs.begin() + 2, std::move(entry));
+  else
+    part.phdrs.push_back(std::move(entry));
 }
 
 // Place the first section of each PT_LOAD to a different page (of maxPageSize).
@@ -3011,6 +3092,14 @@
         sec->writeTo<ELFT>(ctx, ctx.bufferStart + sec->offset, tg);
   }
 
+  // IRIX: rld expects a word relocated against a symbol the object defines
+  // to hold its link-time value already, and adds only the distance the
+  // object moved.
+  if (ctx.arg.osabi == ELFOSABI_IRIX && ctx.arg.writeAddends)
+    for (OutputSection *sec : ctx.outputSections)
+      if (isStaticRelSecType(sec->type))
+        sec->precomputeIRIXRelocs(ctx);
+
   // Finally, check that all dynamic relocation addends were written correctly.
   if (ctx.arg.checkDynamicRelocs && ctx.arg.writeAddends) {
     for (OutputSection *sec : ctx.outputSections)
