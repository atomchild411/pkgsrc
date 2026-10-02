$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: link-time optimization

--- ELF/Arch/MipsArchTree.cpp.orig
+++ ELF/Arch/MipsArchTree.cpp
@@ -15,6 +15,7 @@
 #include "Target.h"
 
 #include "llvm/BinaryFormat/ELF.h"
+#include "llvm/LTO/LTO.h"
 #include "llvm/Support/MipsABIFlags.h"
 
 using namespace llvm;
@@ -358,22 +359,31 @@ uint8_t elf::getMipsFpAbiFlag(Ctx &ctx, InputFile *file, uint8_t oldFlag,
   return oldFlag;
 }
 
-template <class ELFT> static bool isN32Abi(const InputFile &f) {
+template <class ELFT> static bool isN32Abi(Ctx &ctx, const InputFile &f) {
   if (auto *ef = dyn_cast<ELFFileBase>(&f))
     return ef->template getObj<ELFT>().getHeader().e_flags & EF_MIPS_ABI2;
+  // Bitcode: IRIX's is compiled for the ABI its emulation names (see
+  // BitcodeFile's constructor).
+  if (auto *bc = dyn_cast<BitcodeFile>(&f)) {
+    Triple t(bc->obj->getTargetTriple());
+    if (t.isABIN32())
+      return true;
+    if (t.isOSIRIX() && ctx.arg.osabi == ELFOSABI_IRIX)
+      return ctx.arg.mipsN32Abi;
+  }
   return false;
 }
 
 bool elf::isMipsN32Abi(Ctx &ctx, const InputFile &f) {
   switch (ctx.arg.ekind) {
   case ELF32LEKind:
-    return isN32Abi<ELF32LE>(f);
+    return isN32Abi<ELF32LE>(ctx, f);
   case ELF32BEKind:
-    return isN32Abi<ELF32BE>(f);
+    return isN32Abi<ELF32BE>(ctx, f);
   case ELF64LEKind:
-    return isN32Abi<ELF64LE>(f);
+    return isN32Abi<ELF64LE>(ctx, f);
   case ELF64BEKind:
-    return isN32Abi<ELF64BE>(f);
+    return isN32Abi<ELF64BE>(ctx, f);
   default:
     llvm_unreachable("unknown ctx.arg.ekind");
   }
