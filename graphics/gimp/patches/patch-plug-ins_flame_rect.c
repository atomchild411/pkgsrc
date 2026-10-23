$NetBSD$

IRIX: <sys/types.h> defines an accum_t of its own.

--- plug-ins/flame/rect.c.orig
+++ plug-ins/flame/rect.c
@@ -35,6 +35,9 @@
 
 typedef short bucket[4];
 
+/* IRIX's <sys/types.h> has an accum_t of its own (accounting). */
+#define accum_t flame_accum_t
+
 /* if you use longs instead of shorts, you
    get higher quality, and spend more memory */
 
