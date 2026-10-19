$NetBSD: patch-ifdata.c,v 1.1 2017/09/04 09:44:41 leot Exp $

Add NetBSD support.
IRIX: struct ifreq is in <net/if.h>, the SIOC ioctls in <sys/sockio.h>.

--- ifdata.c.orig
+++ ifdata.c
@@ -18,7 +18,7 @@
 	#include <net/if.h>
 #endif
 
-#if defined(__APPLE__) || defined(__OpenBSD__)
+#if defined(__APPLE__) || defined(__OpenBSD__) || defined(__NetBSD__)
 	#define s6_addr16 __u6_addr.__u6_addr16
 	#include <net/if.h>
 #endif
@@ -28,6 +28,11 @@
    #include <net/if.h>
    #include <sys/sockio.h>
 #endif
+
+#if defined(__sgi)
+   #include <net/if.h>
+   #include <sys/sockio.h>
+#endif
 
 #include <netinet/in.h>
 #include <errno.h>
