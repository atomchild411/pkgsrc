$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- [IRIX] Pair sin and cos into IRIX's __sincos, for n32
- N32: sign-extend 32-bit call arguments and return values

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
@@ -3511,7 +3519,16 @@ MipsTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
       UseUpperBits = true;
       [[fallthrough]];
     case CCValAssign::AExt:
-      Arg = DAG.getNode(ISD::ANY_EXTEND, DL, LocVT, Arg);
+      // N32 keeps every 32-bit value sign-extended in its 64-bit register,
+      // pointers included, and callees (IRIX's libc among them) may use the
+      // whole register as an address. A pointer argument has no signext
+      // attribute, so without this it reaches the callee with whatever the
+      // upper half held: say the other member of a struct of two pointers,
+      // which N32 passes in one GPR.
+      if (ABI.IsN32() && VA.getValVT() == MVT::i32 && LocVT == MVT::i64)
+        Arg = DAG.getNode(ISD::SIGN_EXTEND, DL, LocVT, Arg);
+      else
+        Arg = DAG.getNode(ISD::ANY_EXTEND, DL, LocVT, Arg);
       break;
     }
 
@@ -4027,7 +4044,13 @@ MipsTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
       UseUpperBits = true;
       [[fallthrough]];
     case CCValAssign::AExt:
-      Val = DAG.getNode(ISD::ANY_EXTEND, DL, VA.getLocVT(), Val);
+      // As for call arguments: N32 returns 32-bit values (pointers too)
+      // sign-extended to 64 bits.
+      if (ABI.IsN32() && VA.getValVT() == MVT::i32 &&
+          VA.getLocVT() == MVT::i64)
+        Val = DAG.getNode(ISD::SIGN_EXTEND, DL, VA.getLocVT(), Val);
+      else
+        Val = DAG.getNode(ISD::ANY_EXTEND, DL, VA.getLocVT(), Val);
       break;
     case CCValAssign::ZExtUpper:
       UseUpperBits = true;
