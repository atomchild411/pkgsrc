$NetBSD$

IRIX: <sys/param.h> defines TICK.

--- src/mt-timer.c.orig
+++ src/mt-timer.c
@@ -31,6 +31,9 @@
     gdouble target;
 };
 
+#ifdef TICK	/* IRIX <sys/param.h>: nanoseconds per tick */
+#undef TICK
+#endif
 enum
 {
     TICK,
