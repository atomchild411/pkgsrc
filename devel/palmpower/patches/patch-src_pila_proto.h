$NetBSD$

IRIX declares a different getopt; this one is unused.

--- src/pila/proto.h.orig
+++ src/pila/proto.h
@@ -122,7 +122,9 @@
 
 char *skipSpace(char *);
 
+#ifndef __sgi
 int getopt(int, char *[], char *, int *);
+#endif
 
 void help(void);
 
