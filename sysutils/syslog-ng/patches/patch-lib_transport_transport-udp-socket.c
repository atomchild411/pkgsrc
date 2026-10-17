$NetBSD$

IRIX has IP_RECVDSTADDR as the BSDs do, not IP_PKTINFO.

--- lib/transport/transport-udp-socket.c.orig
+++ lib/transport/transport-udp-socket.c
@@ -40,7 +40,7 @@
 
 #if defined(SYSLOG_NG_HAVE_CTRLBUF_IN_MSGHDR)
 
-#if defined(__FreeBSD__) || defined(__OpenBSD__)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__sgi)
 
 GSockAddr *
 _extract_dest_ip4_addr_from_cmsg(struct cmsghdr *cmsg, GSockAddr *bind_addr)
@@ -190,7 +190,7 @@
 
   if (self->super.address_family == AF_INET)
     {
-#if defined(__FreeBSD__) || defined(__OpenBSD__)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__sgi)
       setsockopt(fd, IPPROTO_IP, IP_RECVDSTADDR, &on, sizeof(on));
 #else
       setsockopt(fd, IPPROTO_IP, IP_PKTINFO, &on, sizeof(on));
