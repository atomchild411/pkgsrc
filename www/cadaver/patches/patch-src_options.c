$NetBSD$

IRIX's <stdlib.h> includes <getopt.h> (lib/getopt.h here): rename this file's own struct option.

--- src/options.c.orig
+++ src/options.c
@@ -66,6 +66,8 @@
 /* search option global */
 int searchdepth;
 
+/* IRIX's <stdlib.h> includes <getopt.h>, which is lib/getopt.h here. */
+#define option cadaver_option
 static struct option {
     const char *name;
     enum option_id id;
