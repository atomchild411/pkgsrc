$NetBSD$

IRIX has dlopen.

--- src/util/sys_defs.h.orig
+++ src/util/sys_defs.h
@@ -738,6 +738,7 @@
 #define STATVFS_IN_SYS_STATVFS_H
 #define BROKEN_WRITE_SELECT_ON_NON_BLOCKING_PIPE
 #define CANT_USE_SEND_RECV_MSG
+#define HAS_DLOPEN
 #endif
 
 #if defined(IRIX5)
