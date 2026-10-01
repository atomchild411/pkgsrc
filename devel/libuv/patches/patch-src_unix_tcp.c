$NetBSD$

IRIX has no getifaddrs(): take the AIX path.

--- src/unix/tcp.c.orig
+++ src/unix/tcp.c
@@ -30,8 +30,8 @@
 #include <sys/types.h>
 #include <sys/socket.h>
 
-/* ifaddrs is not implemented on AIX and IBM i PASE */
-#if !defined(_AIX)
+/* ifaddrs is not implemented on AIX and IBM i PASE, nor on IRIX */
+#if !defined(_AIX) && !defined(__sgi)
 #include <ifaddrs.h>
 #endif
 
@@ -228,8 +228,8 @@ static int uv__is_ipv6_link_local(const struct sockaddr* addr) {
 static int uv__ipv6_link_local_scope_id(void) {
   struct sockaddr_in6* a6;
   int rv;
-#if defined(_AIX)
-  /* AIX & IBM i do not have ifaddrs
+#if defined(_AIX) || defined(__sgi)
+  /* AIX & IBM i (and IRIX) do not have ifaddrs
    * so fallback to use uv_interface_addresses */
   uv_interface_address_t* interfaces;
   uv_interface_address_t* ifa;
