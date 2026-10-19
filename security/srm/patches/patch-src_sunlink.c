$NetBSD: patch-src_sunlink.c,v 1.1 2016/10/27 19:49:44 kamil Exp $

Add NetBSD support.
IRIX: signal handlers are void (*)(), and statvfs (its statfs takes four arguments).

--- src/sunlink.c.orig
+++ src/sunlink.c
@@ -105,9 +105,13 @@
 #if defined(__linux__) && !defined(__USE_GNU)
 typedef __sighandler_t sighandler_t;
 #endif
-#if defined(__FreeBSD__) || defined(__OpenBSD__)
+#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
 typedef sig_t sighandler_t;
 #endif
+#if defined(__sgi)
+typedef void (*sighandler_t)();
+#include <sys/statvfs.h>
+#endif
 
 static void sigint_handler(int signo)
 {
@@ -837,8 +841,13 @@
 
 #if defined(HAVE_SYS_VFS_H) || (defined(HAVE_SYS_PARAM_H) && defined(HAVE_SYS_MOUNT_H))
   {
+#if defined(__NetBSD__) || defined(__sgi)
+    struct statvfs fs_stats;
+    if (fstatvfs(srm.fd, &fs_stats) < 0 && errno != ENOSYS)
+#else
     struct statfs fs_stats;
     if (fstatfs(srm.fd, &fs_stats) < 0 && errno != ENOSYS)
+#endif
       {
 	int e=errno;
 	close(srm.fd);
@@ -846,9 +855,9 @@
 	return -1;
       }
 
-#if defined(__linux__)
+#if defined(__linux__) || defined(__sgi)
     srm.buffer_size = fs_stats.f_bsize;
-#elif defined(__FreeBSD__) || defined(__APPLE__)
+#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__)
     srm.buffer_size = fs_stats.f_iosize;
 #else
 #error Please define your platform.
@@ -907,6 +916,7 @@
    and catch only platforms supporting NOUNLINK here.
 
    OpenBSD - doesn't support nounlink (As of 3.1)
+   NetBSD  - doesn't support nounlink (as of 7.99.41)
    FreeBSD - supports nounlink (from 4.4 on?)
    Tru64   - unknown
    MacOS X - doesn't support NOUNLINK (as of 10.3.5)
