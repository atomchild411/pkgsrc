$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: place dynamic relocations in .eh_frame at their output offsets

--- ELF/OutputSections.cpp.orig
+++ ELF/OutputSections.cpp
@@ -894,6 +894,37 @@ std::array<uint8_t, 4> OutputSection::getFiller(Ctx &ctx) {
   return {0, 0, 0, 0};
 }
 
+void OutputSection::precomputeIRIXRelocs(Ctx &ctx) {
+  assert(ctx.arg.osabi == ELFOSABI_IRIX && isStaticRelSecType(type));
+  SmallVector<InputSection *, 0> storage;
+  ArrayRef<InputSection *> sections = getInputSections(*this, storage);
+  for (InputSection *isec : sections) {
+    if (!SyntheticSection::classof(isec) ||
+        !is_contained({ELF::SHT_REL, ELF::SHT_RELA}, isec->type))
+      continue;
+    const auto *sec = cast<RelocationBaseSection>(isec);
+    for (const DynamicReloc &rel : sec->relocs) {
+      // Relocations naming a section symbol (computeRawIRIX) already hold
+      // the full value; only those against a defined symbol by name need it.
+      if (rel.getKind() != DynamicReloc::AgainstSymbol || !rel.sym ||
+          !rel.sym->isDefined())
+        continue;
+      const OutputSection *relOsec = rel.inputSec->getOutputSection();
+      if (!relOsec || relOsec->type == SHT_NOBITS)
+        continue;
+      uint8_t *loc =
+          ctx.bufferStart + relOsec->offset + (rel.getOffset() - relOsec->addr);
+      if (rel.type == R_MIPS_REL32)
+        write32(ctx, loc, rel.sym->getVA(ctx, read32(ctx, loc)));
+      else if (rel.type == ((R_MIPS_64 << 8) | R_MIPS_REL32))
+        write64(ctx, loc, rel.sym->getVA(ctx, read64(ctx, loc)));
+      else
+        InternalErr(ctx, loc) << "unexpected IRIX dynamic relocation "
+                              << rel.type << " against " << rel.sym;
+    }
+  }
+}
+
 void OutputSection::checkDynRelAddends(Ctx &ctx) {
   assert(ctx.arg.writeAddends && ctx.arg.checkDynamicRelocs);
   assert(isStaticRelSecType(type));
@@ -921,13 +952,18 @@ void OutputSection::checkDynRelAddends(Ctx &ctx) {
           (rel.inputSec == ctx.in.ppc64LongBranchTarget.get() ||
            rel.inputSec == ctx.in.igotPlt.get()))
         continue;
-      const uint8_t *relocTarget = ctx.bufferStart + relOsec->offset +
-                                   rel.inputSec->getOffset(rel.offsetInSec);
+      // getOffset() rather than the input section's: see it for .eh_frame.
+      const uint8_t *relocTarget =
+          ctx.bufferStart + relOsec->offset + (rel.getOffset() - relOsec->addr);
       // For SHT_NOBITS the written addend is always zero.
       int64_t writtenAddend =
           relOsec->type == SHT_NOBITS
               ? 0
               : ctx.target->getImplicitAddend(relocTarget, rel.type);
+      // IRIX: against a symbol the output defines, the word holds the
+      // symbol's link-time address too (see precomputeIRIXRelocs).
+      if (ctx.arg.osabi == ELFOSABI_IRIX && rel.sym && rel.sym->isDefined())
+        writtenAddend -= rel.sym->getVA(ctx);
       if (addend != writtenAddend)
         InternalErr(ctx, relocTarget)
             << "wrote incorrect addend value 0x" << utohexstr(writtenAddend)
