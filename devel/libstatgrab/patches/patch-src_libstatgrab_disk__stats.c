$NetBSD$

IRIX file system types.

--- src/libstatgrab/disk_stats.c.orig
+++ src/libstatgrab/disk_stats.c
@@ -59,6 +59,9 @@
 			"ntfs", "nfs"}
 #elif defined(HPUX)
 #define VALID_FS_TYPES {"vxfs", "hfs", "nfs"}
+#elif defined(__sgi)
+#define VALID_FS_TYPES {"xfs", "efs", "nfs", "nfs2", "nfs3", "cachefs", \
+			"iso9660", "dos", "hfs"}
 #elif defined(AIX)
 #define VALID_FS_TYPES {		\
 	"jfs2",		/*  0 */	\
