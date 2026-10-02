$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- [IRIX] Pair sin and cos into IRIX's __sincos, for n32

--- lib/Target/Mips/MipsISelLowering.cpp.orig
+++ lib/Target/Mips/MipsISelLowering.cpp
@@ -459,6 +459,14 @@ MipsTargetLowering::MipsTargetLowering(const MipsTargetMachine &TM,
   setOperationAction(ISD::FCOS,              MVT::f64,   Expand);
   setOperationAction(ISD::FSINCOS,           MVT::f32,   Expand);
   setOperationAction(ISD::FSINCOS,           MVT::f64,   Expand);
+  // IRIX's n32 libm has sincos as __sincos and __sincosf, so a sine and a
+  // cosine of the same value take one call, as MIPSpro makes them. (Only
+  // where errno need not be kept: IRIX's sin and cos set it, and these may
+  // not.) Its n64 libm has only __dcis, which returns them as a complex.
+  if (Subtarget.getTargetTriple().isOSIRIX() && ABI.IsN32()) {
+    setLibcallImpl(RTLIB::SINCOS_F32, RTLIB::__sincosf);
+    setLibcallImpl(RTLIB::SINCOS_F64, RTLIB::__sincos);
+  }
   setOperationAction(ISD::FPOW,              MVT::f32,   Expand);
   setOperationAction(ISD::FPOW,              MVT::f64,   Expand);
   setOperationAction(ISD::FLOG,              MVT::f32,   Expand);
