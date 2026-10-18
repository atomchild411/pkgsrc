$NetBSD$

Big-endian hosts beyond PowerPC (MIPS): the Vorbis decoder and the window icon depend on it.

--- src/common/config.h.orig
+++ src/common/config.h
@@ -39,7 +39,8 @@
 #if defined(__i386__) || defined(__i386)
 #	define LOVE_LITTLE_ENDIAN 1
 #endif
-#if defined(__ppc__) || defined(__ppc)
+#if defined(__ppc__) || defined(__ppc) || \
+	(defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
 #	define LOVE_BIG_ENDIAN 1
 #endif
 
