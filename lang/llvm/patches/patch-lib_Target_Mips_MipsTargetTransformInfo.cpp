$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune
- Report tail calls as supported only with -mips-tail-calls

--- lib/Target/Mips/MipsTargetTransformInfo.cpp.orig
+++ lib/Target/Mips/MipsTargetTransformInfo.cpp
@@ -7,15 +7,39 @@
 //===----------------------------------------------------------------------===//
 
 #include "MipsTargetTransformInfo.h"
+#include "llvm/Support/CommandLine.h"
 
 using namespace llvm;
 
+extern cl::opt<bool> UseMipsTailCalls;
+
+bool MipsTTIImpl::supportsTailCalls() const {
+  return UseMipsTailCalls && !ST->inMips16Mode();
+}
+
 bool MipsTTIImpl::hasDivRemOp(Type *DataType, bool IsSigned) const {
   EVT VT = TLI->getValueType(DL, DataType);
   return TLI->isOperationLegalOrCustom(IsSigned ? ISD::SDIVREM : ISD::UDIVREM,
                                        VT);
 }
 
+// Tuned for the R10000, which issues out of order from a 32-entry window:
+// unroll (LoopMicroOpBufferSize in its model) and interleave loops, so that
+// independent work -- a reduction's partial sums, say -- overlaps. It has 32
+// integer and 32 floating-point registers, and no vector ones.
+unsigned MipsTTIImpl::getNumberOfRegisters(unsigned ClassID) const {
+  if (!ST->isTunedForR10000())
+    return BaseT::getNumberOfRegisters(ClassID);
+  bool Vector = ClassID == 1;
+  return Vector ? 0 : 32;
+}
+
+unsigned MipsTTIImpl::getMaxInterleaveFactor(ElementCount VF) const {
+  if (!ST->isTunedForR10000())
+    return BaseT::getMaxInterleaveFactor(VF);
+  return 4;
+}
+
 bool MipsTTIImpl::isLSRCostLess(const TargetTransformInfo::LSRCost &C1,
                                 const TargetTransformInfo::LSRCost &C2) const {
   // MIPS specific here are "instruction number 1st priority".
