$NetBSD$

IRIX: <sys/param.h> defines a TICK macro, which ate the enum constant.

--- i18n/rbnf.cpp.orig
+++ i18n/rbnf.cpp
@@ -285,6 +285,11 @@
 };
 
 
+/* IRIX's <sys/param.h> defines TICK (nanoseconds per clock tick). */
+#if defined(__sgi) && defined(TICK)
+#undef TICK
+#endif
+
 enum {
     OPEN_ANGLE = 0x003c, /* '<' */
     CLOSE_ANGLE = 0x003e, /* '>' */
