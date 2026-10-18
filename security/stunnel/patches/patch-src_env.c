$NetBSD$

IRIX: define getpeername as <sys/socket.h> declares it.

--- src/env.c.orig
+++ src/env.c
@@ -50,9 +50,15 @@
 #endif
 #undef getpeername
 
+#ifdef __sgi
+/* Defined as declared by the system's <sys/socket.h>. */
+int getpeername(int s, struct sockaddr *sa, socklen_t *len) {
+    struct sockaddr_in *name=(struct sockaddr_in *)sa;
+#else
 int getpeername(int, struct sockaddr_in *, int *);
 
 int getpeername(int s, struct sockaddr_in *name, int *len) {
+#endif
     char *value;
 
     (void)s; /* squash the unused parameter warning */
