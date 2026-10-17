$NetBSD: patch-include_grpc_event__engine_port.h,v 1.8 2023/11/08 14:04:18 nros Exp $

<sys/filio.h> is needed for FIONREAD on Illumos/Solaris
IRIX 6.5 (GPR_IRIX): POSIX sockets, poll, as AIX and Solaris.

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
@@ -27,6 +28,9 @@
 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <unistd.h>
+#if defined(GPR_SOLARIS)
+#include <sys/filio.h>
+#endif
 #elif defined(GPR_WINDOWS)
 #include <winsock2.h>
 #include <ws2tcpip.h>
