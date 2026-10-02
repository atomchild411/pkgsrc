$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- No shrink-wrapping where determineCalleeSaves expands pseudos

--- lib/Target/Mips/MipsSEFrameLowering.h.orig
+++ lib/Target/Mips/MipsSEFrameLowering.h
@@ -26,6 +26,9 @@ public:
   void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
   void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
 
+  /// Shrink-wrapping, except for functions determineCalleeSaves would change.
+  bool enableShrinkWrapping(const MachineFunction &MF) const override;
+
   StackOffset getFrameIndexReference(const MachineFunction &MF, int FI,
                                      Register &FrameReg) const override;
 
