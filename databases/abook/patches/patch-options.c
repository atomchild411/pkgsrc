$NetBSD$

IRIX's <stdlib.h> includes <getopt.h> (./getopt.h here): rename this file's own struct option.

--- options.c.orig
+++ options.c
@@ -39,6 +39,8 @@
 	OT_INT
 };
 
+/* IRIX's <stdlib.h> includes <getopt.h>, which is ./getopt.h here. */
+#define option abook_option
 struct option {
 	char *option;
 	enum opt_type type;
