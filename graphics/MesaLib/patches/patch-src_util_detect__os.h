$NetBSD$

IRIX is a Unix.

--- src/util/detect_os.h.orig
+++ src/util/detect_os.h
@@ -81,7 +81,12 @@
 #define DETECT_OS_UNIX 1
 #endif
 
+#if defined(__sgi)
+#define DETECT_OS_IRIX 1
+#define DETECT_OS_UNIX 1
+#endif
 
+
 /*
  * Make sure DETECT_OS_* are always defined, so that they can be used with #if
  */
@@ -109,6 +114,9 @@
 #ifndef DETECT_OS_HURD
 #define DETECT_OS_HURD 0
 #endif
+#ifndef DETECT_OS_IRIX
+#define DETECT_OS_IRIX 0
+#endif
 #ifndef DETECT_OS_LINUX
 #define DETECT_OS_LINUX 0
 #endif
