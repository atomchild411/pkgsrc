$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/Relocations.cpp.orig
+++ ELF/Relocations.cpp
@@ -803,6 +803,10 @@ static bool maybeReportUndefined(Ctx &ctx, Undefined &sym,
   bool canBeExternal = !sym.isLocal() && sym.visibility() == STV_DEFAULT;
   if (ctx.arg.unresolvedSymbols == UnresolvedPolicy::Ignore && canBeExternal)
     return false;
+  // IRIX libc refers to _rld_new_interface, which rld itself provides.
+  if (ctx.arg.osabi == ELFOSABI_IRIX && canBeExternal &&
+      sym.getName() == "_rld_new_interface")
+    return false;
 
   // clang (as of 2019-06-12) / gcc (as of 8.2.1) PPC64 may emit a .rela.toc
   // which references a switch table in a discarded .rodata/.text section. The
