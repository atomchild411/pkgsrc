$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen
- Report tail calls as supported only with -mips-tail-calls

--- lib/Target/Mips/MipsSEISelLowering.cpp.orig
+++ lib/Target/Mips/MipsSEISelLowering.cpp
@@ -51,7 +51,8 @@ using namespace llvm;
 
 #define DEBUG_TYPE "mips-isel"
 
-static cl::opt<bool>
+// Not static: MipsTargetTransformInfo reports tail call support by it.
+cl::opt<bool>
 UseMipsTailCalls("mips-tail-calls", cl::Hidden,
                     cl::desc("MIPS: permit tail calls."), cl::init(false));
 
@@ -3919,3 +3920,21 @@ MipsSETargetLowering::emitFEXP2_D_1(MachineInstr &MI,
   MI.eraseFromParent(); // The pseudo instruction is gone now.
   return BB;
 }
+
+// Under n32, 32-bit integers and pointers are passed sign-extended to 64 bits,
+// whatever their signedness. Calls the front end emits carry the signext
+// attributes that say so; library calls made during lowering do not, so the
+// callee (MIPSpro-, gcc- or clang-built) can see garbage in the upper half.
+void MipsSETargetLowering::markLibCallAttributes(MachineFunction *MF,
+                                                 unsigned CC,
+                                                 ArgListTy &Args) const {
+  if (!Subtarget.isABI_N32())
+    return;
+
+  for (ArgListEntry &Arg : Args) {
+    if (Arg.Ty->isIntOrPtrTy()) {
+      Arg.IsSExt = true;
+      Arg.IsZExt = false;
+    }
+  }
+}
