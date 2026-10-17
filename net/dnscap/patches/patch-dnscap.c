$NetBSD$

IRIX: the Ethernet header and ETHERTYPE_ names from <net/ethernet.h> (clang IRIX wrapper).

--- dnscap.c.orig
+++ dnscap.c
@@ -71,6 +71,10 @@
 # include <arpa/nameser_compat.h>
 #endif
 
+#ifdef __sgi
+# include <net/ethernet.h>
+#endif
+
 #ifdef __hpux
 # include <net/if.h>
 # include <netinet/if_ether.h>
