$NetBSD$

IRIX: <sys/param.h> defines TICK, the name of a signal index here.

--- src/animation/dzl-animation.c.orig
+++ src/animation/dzl-animation.c
@@ -78,6 +78,8 @@
 };
 
 
+/* IRIX's <sys/param.h> defines TICK (nanoseconds per clock tick). */
+#undef TICK
 enum {
   TICK,
   LAST_SIGNAL
