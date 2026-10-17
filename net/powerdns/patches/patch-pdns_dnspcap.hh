$NetBSD$

IRIX: struct ether_header is in <netinet/if_ether.h>, as on OpenBSD.

--- pdns/dnspcap.hh.orig
+++ pdns/dnspcap.hh
@@ -34,7 +34,7 @@
 #if defined(__NetBSD__)
 #include <net/if.h>
 #include <net/if_ether.h>
-#elif defined (__OpenBSD__)
+#elif defined (__OpenBSD__) || defined(__sgi)
 #include <net/if.h>
 #include <netinet/if_ether.h>
 #elif defined (__SVR4) && defined (__sun)
