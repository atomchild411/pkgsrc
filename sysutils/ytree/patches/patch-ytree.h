$NetBSD$

IRIX: <locale.h> for setlocale().

--- ytree.h.orig
+++ ytree.h
@@ -12,7 +12,7 @@
 #include <ctype.h>
 #include <math.h>
 
-#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__) || defined(SVR4)
+#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__) || defined(SVR4) || defined(__sgi)
 #include <locale.h>
 #endif
 
