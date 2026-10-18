$NetBSD$

IRIX: <stdio.h> declares getopt (with const).

--- cdecl.c.orig
+++ cdecl.c
@@ -131,8 +131,10 @@
 #if !(defined(BSD) && BSD >= 199306) && \
 	!(defined(__sun__) && defined(__svr4__)) && \
 	!(defined(__linux__))
+#ifndef __sgi	/* IRIX: <stdio.h> declares getopt */
   int getopt(int,char **,char *);
 #endif
+#endif
   int main(int, char **);
   int yywrap(void);
   int dostdin(void);
