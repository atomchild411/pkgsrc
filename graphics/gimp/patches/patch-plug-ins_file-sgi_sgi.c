$NetBSD$

IRIX: sgi is a predefined macro (as 1), which G_DEFINE_TYPE (Sgi, sgi, ...) expands.

--- plug-ins/file-sgi/sgi.c.orig
+++ plug-ins/file-sgi/sgi.c
@@ -37,6 +37,9 @@
 
 #include "sgi-lib.h"
 
+/* IRIX compilers predefine sgi (as 1, in GNU modes), as MIPSpro did. */
+#undef sgi
+
 #include "libgimp/stdplugins-intl.h"
 
 
