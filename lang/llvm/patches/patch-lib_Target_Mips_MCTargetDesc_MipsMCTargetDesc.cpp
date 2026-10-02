$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Evaluate branch targets only for branches and calls

--- lib/Target/Mips/MCTargetDesc/MipsMCTargetDesc.cpp.orig
+++ lib/Target/Mips/MCTargetDesc/MipsMCTargetDesc.cpp
@@ -233,10 +233,15 @@ public:
 
   bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                       uint64_t &Target) const override {
+    // Only branches and calls have targets; llvm-objdump asks about every
+    // instruction. Their target is their last operand, an immediate unless
+    // they jump through a register.
+    const MCInstrDesc &Desc = Info->get(Inst.getOpcode());
     unsigned NumOps = Inst.getNumOperands();
-    if (NumOps == 0)
+    if (NumOps == 0 || !(Desc.isBranch() || Desc.isCall()) ||
+        !Inst.getOperand(NumOps - 1).isImm())
       return false;
-    switch (Info->get(Inst.getOpcode()).operands()[NumOps - 1].OperandType) {
+    switch (Desc.operands()[NumOps - 1].OperandType) {
     case MCOI::OPERAND_UNKNOWN:
     case MCOI::OPERAND_IMMEDIATE: {
       // j, jal, jalx, jals
