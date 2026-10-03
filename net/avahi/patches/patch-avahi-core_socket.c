$NetBSD: patch-avahi-core_socket.c,v 1.1 2013/07/05 16:28:43 ryoon Exp $

* Fix build on NetBSD 6.99.23.
  From martin@'s post on tech-pkg@.
* Without IPv6 packet information (IRIX has no IPv6), sending and
  receiving on IPv6 sockets fails (they do not open there either).

--- avahi-core/socket.c.orig	2011-04-25 00:12:18.000000000 +0000
+++ avahi-core/socket.c
@@ -538,7 +538,11 @@
             pkti->ipi_ifindex = interface;
 
         if (src_address)
+#ifdef __linux__
             pkti->ipi_spec_dst.s_addr = src_address->address;
+#else
+            pkti->ipi_addr.s_addr = src_address->address;
+#endif
     }
 #elif defined(IP_MULTICAST_IF)
     if (src_address) {
@@ -571,6 +575,7 @@
     return sendmsg_loop(fd, &msg, 0);
 }
 
+#ifdef IPV6_PKTINFO
 int avahi_send_dns_packet_ipv6(
         int fd,
         AvahiIfIndex interface,
@@ -632,6 +637,21 @@
 
     return sendmsg_loop(fd, &msg, 0);
 }
+#else
+/* No IPv6 packet information (IRIX has no IPv6): IPv6 sockets fail to open,
+   and nothing is sent on them. */
+int avahi_send_dns_packet_ipv6(
+        int fd,
+        AvahiIfIndex interface,
+        AvahiDnsPacket *p,
+        const AvahiIPv6Address *src_address,
+        const AvahiIPv6Address *dst_address,
+        uint16_t dst_port) {
+
+    errno = ENOSYS;
+    return -1;
+}
+#endif
 
 AvahiDnsPacket *avahi_recv_dns_packet_ipv4(
         int fd,
@@ -794,6 +814,7 @@
     return NULL;
 }
 
+#ifdef IPV6_PKTINFO
 AvahiDnsPacket *avahi_recv_dns_packet_ipv6(
         int fd,
         AvahiIPv6Address *ret_src_address,
@@ -916,6 +937,19 @@
 
     return NULL;
 }
+#else
+AvahiDnsPacket *avahi_recv_dns_packet_ipv6(
+        int fd,
+        AvahiIPv6Address *ret_src_address,
+        uint16_t *ret_src_port,
+        AvahiIPv6Address *ret_dst_address,
+        AvahiIfIndex *ret_iface,
+        uint8_t *ret_ttl) {
+
+    errno = ENOSYS;
+    return NULL;
+}
+#endif
 
 int avahi_open_unicast_socket_ipv4(void) {
     struct sockaddr_in local;
