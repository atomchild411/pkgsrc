$NetBSD$

IRIX: <stdio.h> includes <getopt.h>, whose getopt() takes const-qualified arguments.

--- c/type1/source/type1.c.orig
+++ c/type1/source/type1.c
@@ -504,7 +504,9 @@
 }
 
 #ifndef _MSC_VER /* Unix */
+#ifndef __sgi /* IRIX's <stdio.h> declares it (const-qualified) */
 extern int getopt(int argc, char **argv, char *optstring);
+#endif
 extern int optind;
 extern char *optarg;
 #else  /* dos */
