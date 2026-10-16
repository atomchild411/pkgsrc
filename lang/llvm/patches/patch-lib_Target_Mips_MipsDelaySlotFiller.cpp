$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Did not put fake_use into delay slot (#201537)

--- lib/Target/Mips/MipsDelaySlotFiller.cpp.orig
+++ lib/Target/Mips/MipsDelaySlotFiller.cpp
@@ -692,10 +692,17 @@ bool MipsDelaySlotFiller::searchRange(MachineBasicBlock &MBB, IterTy Begin,
     IterTy CurrI = I;
     ++I;
     LLVM_DEBUG(dbgs() << DEBUG_TYPE ": checking instruction: "; CurrI->dump());
-    // Skip debug value.
+
+    if (terminateSearch(*CurrI)) {
+      LLVM_DEBUG(dbgs() << DEBUG_TYPE ": should terminate search: ";
+                 CurrI->dump());
+      break;
+    }
+    // Skip debug and pseudo instructions.
     // Instruction TargetOpcode::JUMP_TABLE_DEBUG_INFO is only used to note
     // jump table debug info.
-    if (CurrI->isDebugInstr() || CurrI->isJumpTableDebugInfo()) {
+    if (CurrI->isDebugInstr() || CurrI->isJumpTableDebugInfo() ||
+        CurrI->isMetaInstruction()) {
       LLVM_DEBUG(dbgs() << DEBUG_TYPE ": ignoring debug instruction: ";
                  CurrI->dump());
       continue;
@@ -709,12 +716,6 @@ bool MipsDelaySlotFiller::searchRange(MachineBasicBlock &MBB, IterTy Begin,
       continue;
     }
 
-    if (terminateSearch(*CurrI)) {
-      LLVM_DEBUG(dbgs() << DEBUG_TYPE ": should terminate search: ";
-                 CurrI->dump());
-      break;
-    }
-
     assert((!CurrI->isCall() && !CurrI->isReturn() && !CurrI->isBranch()) &&
            "Cannot put calls, returns or branches in delay slot.");
 
