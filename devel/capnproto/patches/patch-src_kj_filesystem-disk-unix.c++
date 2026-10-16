$NetBSD$

IRIX has no pwritev() either: the write() loop. Its <sys/mman.h> defines
SHARED and PRIVATE, which are WriteMode::PRIVATE here.

--- src/kj/filesystem-disk-unix.c++.orig
+++ src/kj/filesystem-disk-unix.c++
@@ -47,6 +47,13 @@
 #include "miniposix.h"
 #include <algorithm>
 
+#ifdef __sgi
+// IRIX's <sys/mman.h> defines SHARED and PRIVATE (memcntl's), which are
+// WriteMode::PRIVATE here.
+#undef SHARED
+#undef PRIVATE
+#endif
+
 #if __linux__
 #include <syscall.h>
 #include <linux/fs.h>
@@ -416,7 +423,7 @@
 
     static const byte ZEROS[4096] = { 0 };
 
-#if __APPLE__ || __CYGWIN__ || (defined(__ANDROID__) && __ANDROID_API__ < 24)
+#if __APPLE__ || __CYGWIN__ || (defined(__ANDROID__) && __ANDROID_API__ < 24) || defined(__sgi)
     // Mac & Cygwin & Android API levels 23 and lower doesn't have pwritev().
     while (size > sizeof(ZEROS)) {
       write(offset, ZEROS);
