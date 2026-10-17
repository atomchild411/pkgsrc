$NetBSD$

IRIX 6.5 (GPR_IRIX): POSIX sockets, poll, as AIX and Solaris.

--- src/core/lib/iomgr/port.h.orig
+++ src/core/lib/iomgr/port.h
@@ -163,6 +163,12 @@
 #define GRPC_POSIX_SOCKET 1
 #define GRPC_POSIX_SOCKETUTILS 1
 #define GRPC_POSIX_WAKEUP_FD 1
+#elif defined(GPR_IRIX)
+#define GRPC_HAVE_UNIX_SOCKET 1
+#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
+#define GRPC_POSIX_SOCKET 1
+#define GRPC_POSIX_SOCKETUTILS 1
+#define GRPC_POSIX_WAKEUP_FD 1
 #elif defined(GPR_AIX)
 #define GRPC_HAVE_UNIX_SOCKET 1
 #define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
