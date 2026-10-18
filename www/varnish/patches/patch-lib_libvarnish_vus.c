$NetBSD$

Define VUS_socklen() as vus.h declares it (socklen_t is int on IRIX).

--- lib/libvarnish/vus.c.orig
+++ lib/libvarnish/vus.c
@@ -192,7 +192,7 @@
 	return (VTCP_connected(s));
 }
 
-socklen_t
+unsigned int	/* as vus.h has it; socklen_t is int on IRIX */
 VUS_socklen(const struct sockaddr_un *uds)
 {
 	socklen_t sl;
