$NetBSD$

IRIX: <endian.h> (clang's IRIX wrappers).

--- src/include/portable_endian.h.orig
+++ src/include/portable_endian.h
@@ -3,7 +3,7 @@
 #ifndef __PORTABLE_ENDIAN_H__
 #define __PORTABLE_ENDIAN_H__
 
-#if defined(__linux__) || defined(__CYGWIN__)
+#if defined(__linux__) || defined(__CYGWIN__) || defined(__sgi)
 #	include <endian.h>
 #elif defined(__OpenBSD__)
 #	include <sys/endian.h>
