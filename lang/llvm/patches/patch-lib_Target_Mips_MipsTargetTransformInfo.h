$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune
- Report tail calls as supported only with -mips-tail-calls

--- lib/Target/Mips/MipsTargetTransformInfo.h.orig
+++ lib/Target/Mips/MipsTargetTransformInfo.h
@@ -34,6 +34,14 @@ public:
 
   bool hasDivRemOp(Type *DataType, bool IsSigned) const override;
 
+  /// Only with -mips-tail-calls does lowering make tail calls; otherwise a
+  /// musttail call (coroutine symmetric transfer, for one) cannot be
+  /// lowered, so passes must not create them.
+  bool supportsTailCalls() const override;
+
+  unsigned getNumberOfRegisters(unsigned ClassID) const override;
+  unsigned getMaxInterleaveFactor(ElementCount VF) const override;
+
   bool isLSRCostLess(const TargetTransformInfo::LSRCost &C1,
                      const TargetTransformInfo::LSRCost &C2) const override;
 };
