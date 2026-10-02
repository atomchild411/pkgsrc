$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- No shrink-wrapping where determineCalleeSaves expands pseudos

--- lib/Target/Mips/MipsSEFrameLowering.cpp.orig
+++ lib/Target/Mips/MipsSEFrameLowering.cpp
@@ -821,6 +821,43 @@ static void setAliasRegs(MachineFunction &MF, BitVector &SavedRegs,
     SavedRegs.set(*AI);
 }
 
+// determineCalleeSaves does more than answer: it expands the pseudos that
+// load, store or copy accumulators and DSP condition codes (ExpandPseudo
+// above), and those expansions create virtual registers, which the register
+// scavenger assigns later. Shrink-wrapping calls determineCalleeSaves partway
+// through its scan of the function -- the first time it meets a call's
+// register mask -- and then asserts on the virtual registers in the
+// instructions it scans next ("Unallocated register?!"). Keep shrink-wrapping
+// for every function but those that contain such a pseudo.
+bool MipsSEFrameLowering::enableShrinkWrapping(const MachineFunction &MF) const {
+  for (const MachineBasicBlock &MBB : MF)
+    for (const MachineInstr &MI : MBB)
+      switch (MI.getOpcode()) {
+      case Mips::LOAD_CCOND_DSP:
+      case Mips::STORE_CCOND_DSP:
+      case Mips::LOAD_ACC64:
+      case Mips::LOAD_ACC64DSP:
+      case Mips::LOAD_ACC128:
+      case Mips::STORE_ACC64:
+      case Mips::STORE_ACC64DSP:
+      case Mips::STORE_ACC128:
+      case Mips::ExtractElementF64:
+      case Mips::ExtractElementF64_64:
+        return false;
+      case TargetOpcode::COPY: {
+        Register Src = MI.getOperand(1).getReg();
+        if (Src.isPhysical() && (Mips::ACC64RegClass.contains(Src) ||
+                                 Mips::ACC64DSPRegClass.contains(Src) ||
+                                 Mips::ACC128RegClass.contains(Src)))
+          return false;
+        break;
+      }
+      default:
+        break;
+      }
+  return true;
+}
+
 void MipsSEFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                                BitVector &SavedRegs,
                                                RegScavenger *RS) const {
