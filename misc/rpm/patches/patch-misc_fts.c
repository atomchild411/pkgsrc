$NetBSD: patch-misc_fts.c,v 1.4 2025/02/07 15:06:19 adam Exp $

Detect dirfd(3) and setprogname(3) in configure script.
IRIX has no __errno_location (its stat64 is real).

--- misc/fts.c.orig
+++ misc/fts.c
@@ -37,7 +37,7 @@
 #endif
 
 /* Conditional to set up proper fstat64 implementation */
-#if defined(hpux) || defined(sun) || (defined(__APPLE__) && defined(_DARWIN_FEATURE_ONLY_64_BIT_INODE))
+#if defined(hpux) || defined(sun) || (defined(__APPLE__) && defined(_DARWIN_FEATURE_ONLY_64_BIT_INODE)) || defined(__NetBSD__)
 #   define FTS_FSTAT64(_fd, _sbp)   fstat((_fd), (_sbp))
 #else
 #   define FTS_FSTAT64(_fd, _sbp)   fstat64((_fd), (_sbp))
@@ -72,6 +72,14 @@
 #		define stat64	stat
 #endif
 #endif
+#if defined(__sgi)
+#   define __errno_location()  (&errno)
+#endif
+#if defined(__NetBSD__)
+#   define __errno_location()  (&errno)
+#   define stat64              stat
+#   define __fxstat64(_stat_ver, _fd, _sbp) fstat((_fd), (_sbp))
+#endif
 
 #include "system.h"
 #include <fcntl.h>
