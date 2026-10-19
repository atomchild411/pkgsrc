$NetBSD$

Declare inet_ntoa (with struct in_addr in scope) before sj3compat.h may
rename it to sj3_inet_ntoa (BROKEN_INET_NTOA, set for IRIX); WAIT_ANY
for IRIX.

--- include/sj3compat/sj3compat.h.orig
+++ include/sj3compat/sj3compat.h
@@ -29,6 +29,15 @@
 #include <sys/param.h>
 #endif
 
+/* Declare inet_ntoa before it may be renamed below; IRIX's <arpa/inet.h>
+ * also needs struct in_addr in scope first. */
+#include <netinet/in.h>
+#include <arpa/inet.h>
+
+#ifndef WAIT_ANY	/* IRIX */
+#define WAIT_ANY (-1)
+#endif
+
 #ifndef MAXHOSTNAMELEN
 #define MAXHOSTNAMELEN 256
 #endif
