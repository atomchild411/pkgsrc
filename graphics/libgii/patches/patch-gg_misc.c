$NetBSD$

IRIX does not define _POSIX_SOURCE by default.

--- gg/misc.c.orig
+++ gg/misc.c
@@ -78,7 +78,7 @@
 
 #ifndef HAVE_TMP_PATH
 
-#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE)
+#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || defined(__sgi)
 #define HAVE_TMP_PATH
 		/* this hopefully catches all unix environments */
 		ptr = "/tmp";
