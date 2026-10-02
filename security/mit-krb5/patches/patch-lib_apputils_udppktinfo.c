$NetBSD: patch-lib_apputils_udppktinfo.c,v 1.1 2018/06/15 20:46:01 tez Exp $

Don't use IP_PKTINFO on NetBSD, it doesn't support all required fields.
(based on prior patch-lib_apputils_net-server.c)
The stand-ins for systems without IP_PKTINFO or IPV6_PKTINFO (IRIX) take
the arguments they are called with.

--- ./lib/apputils/udppktinfo.c.orig	2018-06-13 17:53:37.880688500 +0000
+++ ./lib/apputils/udppktinfo.c
@@ -132,7 +132,7 @@
     }
 }
 
-#if defined(HAVE_PKTINFO_SUPPORT) && defined(CMSG_SPACE)
+#if defined(HAVE_PKTINFO_SUPPORT) && defined(CMSG_SPACE) && !defined(__NetBSD__)
 
 /*
  * Check if a socket is bound to a wildcard address.
@@ -210,7 +210,7 @@
 }
 
 #else /* HAVE_IP_PKTINFO || IP_RECVDSTADDR */
-#define check_cmsg_v4_pktinfo(c, t, l, a) 0
+#define check_cmsg_v4_pktinfo(c, t, a) 0
 #endif /* HAVE_IP_PKTINFO || IP_RECVDSTADDR */
 
 #ifdef HAVE_IPV6_PKTINFO
@@ -240,7 +240,7 @@
     return 0;
 }
 #else /* HAVE_IPV6_PKTINFO */
-#define check_cmsg_v6_pktinfo(c, t, l, a) 0
+#define check_cmsg_v6_pktinfo(c, t, a) 0
 #endif /* HAVE_IPV6_PKTINFO */
 
 static int
@@ -363,7 +363,7 @@
 }
 
 #else /* HAVE_IP_PKTINFO || IP_SENDSRCADDR */
-#define set_msg_from_ipv4(m, c, f, l, a) EINVAL
+#define set_msg_from_ipv4(m, c, f, a) EINVAL
 #endif /* HAVE_IP_PKTINFO || IP_SENDSRCADDR */
 
 #ifdef HAVE_IPV6_PKTINFO
@@ -398,7 +398,7 @@
 }
 
 #else /* HAVE_IPV6_PKTINFO */
-#define set_msg_from_ipv6(m, c, f, l, a) EINVAL
+#define set_msg_from_ipv6(m, c, f, a) EINVAL
 #endif /* HAVE_IPV6_PKTINFO */
 
 static krb5_error_code
