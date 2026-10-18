$NetBSD$

IRIX as the BSDs; big-endian hosts beyond PowerPC (MIPS).

--- src/common/config.h.orig
+++ src/common/config.h
@@ -48,13 +48,14 @@
 #		define LOVE_MACOSX 1
 #	endif
 #endif
-#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
+#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__sgi)
 // I know it's not linux, but it seems most "linux-only" code is bsd-compatible
 #	define LOVE_LINUX 1
 #endif
 
 // Endianness.
-#if defined(__ppc__) || defined(__ppc) || defined(__powerpc__) || defined(__powerpc)
+#if defined(__ppc__) || defined(__ppc) || defined(__powerpc__) || defined(__powerpc) || \
+	(defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
 #	define LOVE_BIG_ENDIAN 1
 #else
 #	define LOVE_LITTLE_ENDIAN 1
