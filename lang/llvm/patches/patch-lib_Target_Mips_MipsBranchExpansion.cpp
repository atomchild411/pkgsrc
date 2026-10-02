$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Check branch ranges again after any hazard nops (MIPS I-III)
- MFLO hazard: count the nops anywhere in the instruction's bundle

--- lib/Target/Mips/MipsBranchExpansion.cpp.orig
+++ lib/Target/Mips/MipsBranchExpansion.cpp
@@ -225,6 +225,22 @@ static std::pair<Iter, bool> getNextMachineInstr(Iter Position,
   return std::make_pair(Instr, false);
 }
 
+/// A nop: the NOP pseudo, or sll $zero, $zero, 0 as insertNop builds it.
+static bool isNop(const MachineInstr &MI) {
+  switch (MI.getOpcode()) {
+  case Mips::NOP:
+    return true;
+  case Mips::SLL:
+  case Mips::SLL_MM:
+  case Mips::SLL_MMR6:
+    return MI.getOperand(0).getReg() == Mips::ZERO &&
+           MI.getOperand(1).getReg() == Mips::ZERO &&
+           MI.getOperand(2).getImm() == 0;
+  default:
+    return false;
+  }
+}
+
 /// Iterate over list of Br's operands and search for a MachineBasicBlock
 /// operand.
 static MachineBasicBlock *getTargetMBB(const MachineInstr &Br) {
@@ -768,11 +784,17 @@ bool MipsBranchExpansion::handleMFLOSlot(Pred Predicate, Safe SafeInSlot) {
         if (LastInstInFunction)
           continue;
         if (!SafeInSlot(*IInSlot, *I)) {
-          Changed = true;
-          TII->insertNop(*(I->getParent()), std::next(I), I->getDebugLoc())
-              ->bundleWithPred();
-          NumInsertedNops++;
-          if (IsMFLOMFHI(I->getOpcode())) {
+          // Two nops after mflo/mfhi, one after the instruction between;
+          // fewer if an earlier round put some there already. They go at the
+          // end of I's bundle, after a delay slot if I has one: count the
+          // nops anywhere in it.
+          unsigned Needed = IsMFLOMFHI(I->getOpcode()) ? 2 : 1;
+          for (MachineBasicBlock::instr_iterator N = std::next(I->getIterator());
+               Needed && N != FI->instr_end() && N->isBundledWithPred(); ++N)
+            if (isNop(*N))
+              --Needed;
+          for (; Needed; --Needed) {
+            Changed = true;
             TII->insertNop(*(I->getParent()), std::next(I), I->getDebugLoc())
                 ->bundleWithPred();
             NumInsertedNops++;
@@ -812,8 +834,7 @@ bool MipsBranchExpansion::handleSlot(Pred Predicate, Safe SafeInSlot) {
 
       if (LastInstInFunction || !SafeInSlot(*IInSlot, *I)) {
         MachineBasicBlock::instr_iterator Iit = I->getIterator();
-        if (std::next(Iit) == FI->end() ||
-            std::next(Iit)->getOpcode() != Mips::NOP) {
+        if (std::next(Iit) == FI->end() || !isNop(*std::next(Iit))) {
           Changed = true;
           TII->insertNop(*(I->getParent()), std::next(I), I->getDebugLoc())
               ->bundleWithPred();
@@ -960,16 +981,23 @@ bool MipsBranchExpansion::runOnMachineFunction(MachineFunction &MF) {
   bool Changed = longBranchChanged || forbiddenSlotChanged ||
                  fpuDelaySlotChanged || loadDelaySlotChanged || MfloChanged;
 
-  // Then run them alternatively while there are changes.
-  while (forbiddenSlotChanged) {
+  // Then run them alternatively while there are changes. Every hazard
+  // handler inserts nops, which can push a branch out of range, so branches
+  // are checked again after any of them changed something -- not only the
+  // forbidden slot one: on MIPS I-III the FPU delay slot nops alone can do
+  // it. (The handlers leave nops an earlier round inserted alone.)
+  bool HazardsChanged = forbiddenSlotChanged || fpuDelaySlotChanged ||
+                        loadDelaySlotChanged || MfloChanged;
+  while (HazardsChanged) {
     longBranchChanged = handlePossibleLongBranch();
+    forbiddenSlotChanged = handleForbiddenSlot();
     fpuDelaySlotChanged = handleFPUDelaySlot();
     loadDelaySlotChanged = handleLoadDelaySlot();
     MfloChanged = handleMFLO();
-    if (!longBranchChanged && !fpuDelaySlotChanged && !loadDelaySlotChanged &&
-        !MfloChanged)
+    HazardsChanged = forbiddenSlotChanged || fpuDelaySlotChanged ||
+                     loadDelaySlotChanged || MfloChanged;
+    if (!longBranchChanged && !HazardsChanged)
       break;
-    forbiddenSlotChanged = handleForbiddenSlot();
   }
 
   return Changed;
