$NetBSD$

struct sockaddr_in needs <netinet/in.h> (Solaris pulls it in through other headers; IRIX does not).

--- addrs_dlpi.c.orig
+++ addrs_dlpi.c
@@ -26,6 +26,7 @@
 #include <sys/socket.h>
 #include <sys/dlpi.h>
 #include <net/if.h>
+#include <netinet/in.h>
 
 #include "dlcommon.h"
 
