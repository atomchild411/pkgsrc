$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- [IRIX] Pair sin and cos into IRIX's __sincos, for n32

--- include/llvm/IR/RuntimeLibcalls.td.orig
+++ include/llvm/IR/RuntimeLibcalls.td
@@ -991,6 +991,9 @@ def __sincos_stret : RuntimeLibcallImpl<SINCOS_STRET_F64>;
 
 def sincosf : RuntimeLibcallImpl<SINCOS_F32>;
 def sincos : RuntimeLibcallImpl<SINCOS_F64>;
+// IRIX's libm, for n32: sincos(x, &sin, &cos) under reserved names.
+def __sincosf : RuntimeLibcallImpl<SINCOS_F32>;
+def __sincos : RuntimeLibcallImpl<SINCOS_F64>;
 defm sincos : LibmLongDoubleLibCall;
 
 def bzero : RuntimeLibcallImpl<BZERO>;
