$NetBSD$

IRIX <sys/types.h> defines tid_t.

--- lib/ext2fs/jfs_compat.h.orig
+++ lib/ext2fs/jfs_compat.h
@@ -31,6 +31,9 @@
 #define le64_to_cpu(x)	ext2fs_le64_to_cpu(x)
 #define be64_to_cpu(x)	ext2fs_be64_to_cpu(x)
 
+/* IRIX's <sys/types.h> has a tid_t (a thread ID): rename the journal's. */
+#include <sys/types.h>
+#define tid_t ext2fs_tid_t
 typedef unsigned int tid_t;
 typedef struct journal_s journal_t;
 typedef struct kdev_s *kdev_t;
