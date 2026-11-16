$NetBSD$

Take the host byte order from the compiler on every big-endian CPU, not
only PowerPC: on MIPS the binary reader swapped big-endian model, skeleton,
animation and map data it should have read as is, and the game stopped
with "Exception catched: vector".

--- Source/Utils/private.h.orig
+++ Source/Utils/private.h
@@ -66,7 +66,8 @@
 #endif
 
 #ifndef BinIO_BYTE_ORDER
-#if defined(__ppc__) || defined(__POWERPC__)
+#if defined(__ppc__) || defined(__POWERPC__) || \
+    (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
 #define BinIO_BYTE_ORDER BinIO_BIG_ENDIAN_BYTE_ORDER
 #else
 #define BinIO_BYTE_ORDER BinIO_LITTLE_ENDIAN_BYTE_ORDER
