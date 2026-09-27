$NetBSD$

IRIX 6.5 has no native sockaddr_in6: libevent's replacement must carry
sin6_scope_id (and sin6_flowinfo), which evutil.c assigns.

--- ipv6-internal.h.orig
+++ ipv6-internal.h
@@ -66,6 +66,14 @@
 	sa_family_t sin6_family;
 	ev_uint16_t sin6_port;
 	struct in6_addr sin6_addr;
+	/* evutil.c assigns sin6_scope_id unconditionally (three sites), so the
+	 * replacement struct has to carry it or libevent does not compile at all
+	 * on a platform lacking a native sockaddr_in6 -- which is any platform
+	 * that needs this struct in the first place. Appended rather than placed
+	 * in RFC 2553 order because nothing hands this struct to the OS: the
+	 * whole point is that the OS has no IPv6 sockaddr of its own. */
+	ev_uint32_t sin6_flowinfo;
+	ev_uint32_t sin6_scope_id;
 };
 #endif
 
