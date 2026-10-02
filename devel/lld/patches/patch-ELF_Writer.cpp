$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: R_MIPS_LITERAL, R_MIPS_PJUMP, and .sbss before .bss

--- ELF/Writer.cpp.orig
+++ ELF/Writer.cpp
@@ -777,6 +777,12 @@ unsigned elf::getSectionRank(Ctx &ctx, OutputSection &osec) {
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
@@ -1936,6 +1942,17 @@ template <class ELFT> void Writer<ELFT>::finalizeSections() {
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
@@ -2010,6 +2027,18 @@ template <class ELFT> void Writer<ELFT>::finalizeSections() {
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
@@ -2047,9 +2076,17 @@ template <class ELFT> void Writer<ELFT>::finalizeSections() {
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
@@ -2316,8 +2353,10 @@ Writer<ELFT>::createPhdrs(Partition &part) {
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
@@ -2439,8 +2478,18 @@ Writer<ELFT>::createPhdrs(Partition &part) {
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
@@ -2523,7 +2572,11 @@ void Writer<ELFT>::addPhdrForSection(Partition &part, unsigned shType,
 
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
@@ -3011,6 +3064,14 @@ template <class ELFT> void Writer<ELFT>::writeSections() {
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
