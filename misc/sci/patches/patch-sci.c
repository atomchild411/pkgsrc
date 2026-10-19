$NetBSD$

Do not declare usleep: <unistd.h> does (with useconds_t on IRIX).

--- sci.c.orig
+++ sci.c
@@ -217,9 +217,7 @@
 int externField(int fieldNumber);
 int picBox(int n);
 
-#ifdef HAVE_USLEEP
-int usleep(unsigned long usec);
-#endif /* HAVE_USLEEP */
+/* usleep: declared by <unistd.h> (with another type on IRIX) */
 #ifndef __USE_BSD
 int gethostname(char *name, size_t len);
 #endif /* __USE_BSD */
