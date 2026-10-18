$NetBSD$

IRIX: timercmp only in SGI and BSD modes.

--- Meter.c.orig
+++ Meter.c
@@ -18,6 +18,13 @@
 
 #include "CRT.h"
 #include "Macros.h"
+
+#ifndef timercmp
+/* IRIX defines it only in SGI and BSD modes (and wrongly for <= and >=). */
+#define timercmp(a, b, CMP) \
+   (((a)->tv_sec == (b)->tv_sec) ? \
+    ((a)->tv_usec CMP (b)->tv_usec) : ((a)->tv_sec CMP (b)->tv_sec))
+#endif
 #include "Object.h"
 #include "ProvideCurses.h"
 #include "RichString.h"
