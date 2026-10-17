$NetBSD$

Big-endian TWO_PIX_32 and THREE_PIX_32, as the big-endian TWO_PIX and THREE_PIX have them (the latter's order is upstream's guess).

--- src/intf/video/scalers/epx.cpp.orig
+++ src/intf/video/scalers/epx.cpp
@@ -36,6 +36,8 @@
 	#define TWO_PIX(left,right) ((right) | ((left) << 16))
 	#define THREE_PIX(left,middle,right) uint48((middle) | ((left) << 16), (right)) // is this right?
 //	#define THREE_PIX(left,middle,right) uint48((right) | ((middle) << 16), (left)) // or this?
+	#define TWO_PIX_32(left,right) (CONVERT_16_TO_32(right) | ((uint64)CONVERT_16_TO_32(left) << 32))
+	#define THREE_PIX_32(left,middle,right) uint96(CONVERT_16_TO_32(middle) | ((uint64)CONVERT_16_TO_32(left) << 32), CONVERT_16_TO_32(right))
 #endif
 
 // shared EPX-type loop macros
