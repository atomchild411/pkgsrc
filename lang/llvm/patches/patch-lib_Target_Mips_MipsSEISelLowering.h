$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen

--- lib/Target/Mips/MipsSEISelLowering.h.orig
+++ lib/Target/Mips/MipsSEISelLowering.h
@@ -62,6 +62,9 @@ class TargetRegisterClass;
 
     const TargetRegisterClass *getRepRegClassFor(MVT VT) const override;
 
+    void markLibCallAttributes(MachineFunction *MF, unsigned CC,
+                               ArgListTy &Args) const override;
+
   private:
     bool isEligibleForTailCallOptimization(
         const CCState &CCInfo, unsigned NextStackOffset,
