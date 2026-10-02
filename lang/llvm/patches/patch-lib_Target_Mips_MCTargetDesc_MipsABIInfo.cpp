$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen

--- lib/Target/Mips/MCTargetDesc/MipsABIInfo.cpp.orig
+++ lib/Target/Mips/MCTargetDesc/MipsABIInfo.cpp
@@ -70,7 +70,8 @@ MipsABIInfo MipsABIInfo::computeTargetABI(const Triple &TT, StringRef CPU,
   assert(Options.getABIName().empty() && "Unknown ABI option for MIPS");
 
   if (TT.isMIPS64())
-    return MipsABIInfo::N64();
+    // IRIX's native 64-bit-CPU ABI is n32.
+    return TT.isOSIRIX() ? MipsABIInfo::N32() : MipsABIInfo::N64();
   return MipsABIInfo::O32();
 }
 
