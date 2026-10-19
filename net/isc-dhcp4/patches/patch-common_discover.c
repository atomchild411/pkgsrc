$NetBSD$

IRIX has no sa_len either.

--- common/discover.c.orig
+++ common/discover.c
@@ -459,8 +459,8 @@
 	 * result in a record with no address (ifa_addr).
 	 */
 	if (ifaces->next->ifa_addr != NULL) {
-/* Linux lacks the sa_len member in struct sockaddr. */
-#if defined(__linux)
+/* Linux and IRIX lack the sa_len member in struct sockaddr. */
+#if defined(__linux) || defined(__sgi)
 		if (ifaces->next->ifa_addr->sa_family == AF_INET)
 			sa_len = sizeof(struct sockaddr_in);
 		else if (ifaces->next->ifa_addr->sa_family == AF_INET6)
