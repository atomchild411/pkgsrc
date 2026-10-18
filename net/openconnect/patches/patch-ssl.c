$NetBSD$

IRIX: statvfs, as on Solaris.

--- ssl.c.orig
+++ ssl.c
@@ -29,7 +29,7 @@
 #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__OpenBSD__) || defined(__APPLE__)
 #include <sys/param.h>
 #include <sys/mount.h>
-#elif defined(__sun__) || defined(__NetBSD__) || defined(__DragonFly__)
+#elif defined(__sun__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__sgi)
 #include <sys/statvfs.h>
 #elif defined(__GNU__)
 #include <sys/statfs.h>
@@ -622,7 +622,7 @@
 	return -EIO;
 }
 
-#if defined(__sun__) || defined(__NetBSD__) || defined(__DragonFly__)
+#if defined(__sun__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__sgi)
 int openconnect_passphrase_from_fsid(struct openconnect_info *vpninfo)
 {
 	struct statvfs buf;
