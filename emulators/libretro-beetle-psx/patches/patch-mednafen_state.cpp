$NetBSD$

Big-endian hosts: map the old endian helper names.

--- mednafen/state.cpp.orig
+++ mednafen/state.cpp
@@ -26,6 +26,13 @@
 
 #include "mednafen-endian.h"
 
+#ifdef MSB_FIRST /* big-endian hosts: the names below are gone from mednafen-endian */
+#define Endian_A64_LE_to_NE Endian_A64_NE_LE
+#define Endian_A32_LE_to_NE Endian_A32_NE_LE
+#define Endian_A16_LE_to_NE Endian_A16_NE_LE
+#define FlipByteOrder(p, n) Endian_V_NE_LE(p, n)
+#endif
+
 #define RLSB 		MDFNSTATE_RLSB	//0x80000000
 
 //Fast Save States exclude string labels from variables in the savestate, and are at least 20% faster.
