$NetBSD: patch-src_device__info.c,v 1.2 2021/03/04 10:02:44 nia Exp $

https://github.com/dosfstools/dosfstools/commit/8a917ed2afb2dd2a165a93812b6f52b9060eec5f.patch

Support netbsd's spelling for statfs.
IRIX has MOUNTED, not _PATH_MOUNTED.

--- src/device_info.c.orig
+++ src/device_info.c
@@ -24,7 +24,10 @@
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/ioctl.h>
-#include <sys/sysmacros.h>
+
+#ifdef HAVE_SYS_SYSMACROS_H
+# include <sys/sysmacros.h>
+#endif
 
 #ifdef HAVE_LINUX_LOOP_H
 #include <linux/loop.h>
@@ -33,6 +36,9 @@
 #if HAVE_DECL_GETMNTENT
 #include <paths.h>
 #include <mntent.h>
+#ifndef _PATH_MOUNTED
+#define _PATH_MOUNTED MOUNTED /* IRIX: <mntent.h>'s name for it */
+#endif
 #endif
 
 #if HAVE_DECL_GETMNTINFO
@@ -334,7 +340,11 @@
 #endif
 
 #if HAVE_DECL_GETMNTINFO
+#ifdef __NetBSD__
+    struct statvfs *stat;
+#else
     struct statfs *stat;
+#endif
     int count, i;
 
     count = getmntinfo(&stat, 0);
