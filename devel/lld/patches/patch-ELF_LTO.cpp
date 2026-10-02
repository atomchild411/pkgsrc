$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: link-time optimization

--- ELF/LTO.cpp.orig
+++ ELF/LTO.cpp
@@ -48,6 +48,10 @@ static lto::Config createConfig(Ctx &ctx) {
   // LLD supports the new relocations and address-significance tables.
   c.Options = initTargetOptionsFromCodeGenFlags();
   c.Options.EmitAddrsig = true;
+  // IRIX: compile for the ABI the emulation names, which IRIX triples do not.
+  if (ctx.arg.osabi == ELFOSABI_IRIX && c.Options.MCOptions.ABIName.empty())
+    c.Options.MCOptions.ABIName =
+        ctx.arg.mipsN32Abi ? "n32" : (ctx.arg.is64 ? "n64" : "o32");
   for (StringRef C : ctx.arg.mllvmOpts)
     c.MllvmArgs.emplace_back(C.str());
 
@@ -91,7 +95,9 @@ static lto::Config createConfig(Ctx &ctx) {
     c.RelocModel = *relocModel;
   else if (ctx.arg.relocatable)
     c.RelocModel = std::nullopt;
-  else if (ctx.arg.isPic)
+  // IRIX executables are position-independent too, as MIPSpro makes them:
+  // rld has no copy relocations or PLT for non-PIC code to rely on.
+  else if (ctx.arg.isPic || ctx.arg.osabi == ELFOSABI_IRIX)
     c.RelocModel = Reloc::PIC_;
   else
     c.RelocModel = Reloc::Static;
