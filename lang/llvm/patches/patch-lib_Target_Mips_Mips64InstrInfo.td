$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Only a narrow AssertSext makes i64->i32 truncation free

--- lib/Target/Mips/Mips64InstrInfo.td.orig
+++ lib/Target/Mips/Mips64InstrInfo.td
@@ -71,6 +71,13 @@ def assertzext_lt_i32 : PatFrag<(ops node:$src), (assertzext node:$src), [{
   return cast<VTSDNode>(N->getOperand(1))->getVT().bitsLT(MVT::i32);
 }]>;
 
+// An AssertSext from i32 or narrower: the low word is then itself sign
+// extended. A wider one (SelectionDAG asserts the sign bits it knows of a
+// value live across blocks, e.g. i36) says nothing about bit 31.
+def assertsext_le_i32 : PatFrag<(ops node:$src), (assertsext node:$src), [{
+  return cast<VTSDNode>(N->getOperand(1))->getVT().bitsLE(MVT::i32);
+}]>;
+
 //===----------------------------------------------------------------------===//
 // Instructions specific format
 //===----------------------------------------------------------------------===//
@@ -800,7 +807,7 @@ let AdditionalPredicates = [NotInMicroMips] in {
   defm : SetgeImmPats<GPR64, XORi, SLTi64, SLTiu64>, ISA_MIPS3, GPR_64;
 }
 // truncate
-def : MipsPat<(trunc (assertsext GPR64:$src)),
+def : MipsPat<(trunc (assertsext_le_i32 GPR64:$src)),
               (EXTRACT_SUBREG GPR64:$src, sub_32)>, ISA_MIPS3, GPR_64;
 // The forward compatibility strategy employed by MIPS requires us to treat
 // values as being sign extended to an infinite number of bits. This allows
