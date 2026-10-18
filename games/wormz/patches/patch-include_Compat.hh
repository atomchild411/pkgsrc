$NetBSD$

IRIX: <math.h> defines PI.

--- include/Compat.hh.orig
+++ include/Compat.hh
@@ -24,6 +24,9 @@
 }
 
 #if !defined(__NetBSD__) && !defined(__DragonFly__) && !defined(__sun)
+#ifdef PI	/* IRIX <math.h> */
+#undef PI
+#endif
 const double PI=3.1415926535797;
 #endif
 
