$NetBSD$

IRIX: no ARP entries (its struct arpreq has no arp_dev).

--- src/modules/proto_dhcp/dhcp.c.orig
+++ src/modules/proto_dhcp/dhcp.c
@@ -1911,7 +1911,8 @@
 	return 0;
 }
 
-#ifdef SIOCSARP
+/* IRIX has SIOCSARP, but its struct arpreq has no arp_dev. */
+#if defined(SIOCSARP) && !defined(__sgi)
 int fr_dhcp_add_arp_entry(int fd, char const *interface,
 			  VALUE_PAIR *macaddr, VALUE_PAIR *ip)
 {
