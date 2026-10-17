$NetBSD$

IRIX: no struct ip_mreqn; SIOCGIFADDR is in <sys/sockio.h>.

--- src/minissdpc.c.orig
+++ src/minissdpc.c
@@ -71,13 +71,13 @@
 
 #include "miniupnpc_socketdef.h"
 
-#if !defined(__DragonFly__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(__CYGWIN__) && !defined(__sun) && !defined(__GNU__) && !defined(__FreeBSD_kernel__) && !defined(__HAIKU__)
+#if !defined(__DragonFly__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__APPLE__) && !defined(_WIN32) && !defined(__CYGWIN__) && !defined(__sun) && !defined(__GNU__) && !defined(__FreeBSD_kernel__) && !defined(__HAIKU__) && !defined(__sgi)
 #define HAS_IP_MREQN
 #endif
 
 #ifndef _WIN32
 #include <sys/ioctl.h>
-#if defined(__sun) || defined(__HAIKU__)
+#if defined(__sun) || defined(__HAIKU__) || defined(__sgi)
 #include <sys/sockio.h>
 #endif
 #endif
