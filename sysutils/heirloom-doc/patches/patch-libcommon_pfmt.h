$NetBSD$

IRIX declares gettxt() in <nl_types.h> and <unistd.h>: include them before defining the macro.

--- libcommon/pfmt.h.orig
+++ libcommon/pfmt.h
@@ -43,4 +43,7 @@
 extern int	setuxlabel(const char *label);
 
 #define	setcat(s)	(s)
+/* IRIX declares gettxt() in these: include them before the macro. */
+#include <nl_types.h>
+#include <unistd.h>
 #define	gettxt(n, s)	(s)
