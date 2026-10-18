$NetBSD$

IRIX: <endian.h> (clang's IRIX wrappers).

--- include/portable_endian.h.orig
+++ include/portable_endian.h
@@ -13,7 +13,7 @@
 
 #endif
 
-#if defined(__linux__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__CYGWIN__) || defined(__sgi)
 
 #	include <endian.h>
 
