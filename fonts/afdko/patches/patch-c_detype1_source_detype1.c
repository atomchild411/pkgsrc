$NetBSD$

IRIX: <stdio.h> includes <getopt.h>, whose getopt() takes const-qualified arguments.

--- c/detype1/source/detype1.c.orig
+++ c/detype1/source/detype1.c
@@ -524,7 +524,9 @@
 }
 
 #ifndef _MSC_VER /* Unix */
+#ifndef __sgi /* IRIX's <stdio.h> declares it (const-qualified) */
 extern int getopt(int argc, char **argv, char *optstring);
+#endif
 extern int optind;
 extern char *optarg;
 #else  /* dos */
