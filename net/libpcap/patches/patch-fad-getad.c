$NetBSD: patch-fad-getad.c,v 1.2 2024/09/01 09:47:09 adam Exp $

Re-order includes to avoid bpf_program re-definition.

Include <net/if_dl.h> where AF_LINK exists: without sa_len, get_sa_len()
sizes struct sockaddr_dl itself (IRIX has AF_LINK and getifaddrs, and no
sa_len).

--- fad-getad.c.orig
+++ fad-getad.c
@@ -45,11 +45,8 @@
 #include <stdlib.h>
 #include <string.h>
 #include <ifaddrs.h>
-
-#include "pcap-int.h"
-
-#ifdef HAVE_OS_PROTO_H
-#include "os-proto.h"
+#ifdef AF_LINK
+#include <net/if_dl.h>		/* struct sockaddr_dl, sized in get_sa_len() */
 #endif
 
 /*
@@ -75,6 +72,12 @@
 # endif /* HAVE_NETPACKET_PACKET_H */
 #endif /* (defined(__linux__) || defined(__Lynx__)) && defined(AF_PACKET) */
 
+#include "pcap-int.h"
+
+#ifdef HAVE_OS_PROTO_H
+#include "os-proto.h"
+#endif
+
 /*
  * This is fun.
  *
