$NetBSD$

Define timercmp where <sys/time.h> has none (IRIX outside SGI mode), as for Solaris.

--- psycopg/pqpath.c.orig
+++ psycopg/pqpath.c
@@ -59,6 +59,13 @@
 #include "aix_support.h"
 #else
 #include <sys/time.h>
+#ifndef timercmp
+/* As in solaris_support.h: IRIX declares none outside SGI mode. */
+#define timercmp(a, b, cmp)          \
+  (((a)->tv_sec == (b)->tv_sec) ?    \
+   ((a)->tv_usec cmp (b)->tv_usec) : \
+   ((a)->tv_sec  cmp (b)->tv_sec))
+#endif
 #endif
 
 extern HIDDEN PyObject *psyco_DescriptionType;
