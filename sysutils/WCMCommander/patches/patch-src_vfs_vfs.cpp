$NetBSD: patch-src_vfs_vfs.cpp,v 1.2 2015/09/08 13:21:46 wiz Exp $

Use BSD headers on NetBSD, and use statvfs (statfs was removed).
https://github.com/corporateshark/WCMCommander/pull/509
IRIX's statfs() takes four arguments: use statvfs there too.

--- src/vfs/vfs.cpp.orig
+++ src/vfs/vfs.cpp
@@ -1113,9 +1113,15 @@
 // for statfs()
 #ifdef __linux__
 #  include <sys/statfs.h>
-#elif defined(__FreeBSD__) || defined(__OpenBSD__)
+#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
 #  include <sys/param.h>
 #  include <sys/mount.h>
+#  if defined(__NetBSD__)
+#    define statfs statvfs
+#  endif
+#elif defined(__sgi)
+#  include <sys/statvfs.h>
+#  define statfs statvfs
 #endif
 
 #ifdef __linux__
