$NetBSD$

IRIX 6.5 (GPR_IRIX): as for net/grpc.

--- include/grpc/event_engine/port.h.orig
+++ include/grpc/event_engine/port.h
@@ -20,6 +20,7 @@
 #if defined(GPR_ANDROID) || defined(GPR_LINUX) || defined(GPR_APPLE) ||     \
     defined(GPR_FREEBSD) || defined(GPR_OPENBSD) || defined(GPR_SOLARIS) || \
     defined(GPR_AIX) || defined(GPR_NACL) || defined(GPR_FUCHSIA) ||        \
+    defined(GPR_IRIX) ||                                                    \
     defined(GRPC_POSIX_SOCKET) || defined(GPR_NETBSD)
 #define GRPC_EVENT_ENGINE_POSIX
 #include <arpa/inet.h>
