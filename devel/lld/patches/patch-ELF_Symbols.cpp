$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/Symbols.cpp.orig
+++ ELF/Symbols.cpp
@@ -341,6 +341,11 @@ bool elf::computeIsPreemptible(Ctx &ctx, const Symbol &sym) {
   if (!sym.isDefined())
     return !sym.isUndefined() || ctx.arg.zDynamicUndefined;
 
+  // IRIX's rld looks up some symbols in every executable by name and needs
+  // a GOT entry for each (see markIRIXRldSymbols).
+  if (ctx.arg.osabi == ELFOSABI_IRIX && sym.inDynamicList)
+    return true;
+
   if (!ctx.arg.shared)
     return false;
 
@@ -372,6 +377,9 @@ void elf::parseVersionAndComputeIsPreemptible(Ctx &ctx) {
     }
     if (!sym->isDefined() && !sym->isCommon()) {
       sym->isPreemptible = computeIsPreemptible(ctx, *sym);
+    } else if (ctx.arg.osabi == ELFOSABI_IRIX && sym->inDynamicList) {
+      sym->isExported = true;
+      sym->isPreemptible = true;
     } else if (ctx.arg.exportDynamic &&
                (sym->isUsedInRegularObj || !sym->ltoCanOmit)) {
       sym->isExported = true;
