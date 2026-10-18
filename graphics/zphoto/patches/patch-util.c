$NetBSD$

IRIX declares vasprintf too (with a va_list).

--- util.c.orig
+++ util.c
@@ -79,7 +79,7 @@
     va_end(args);
 }
 
-#if defined(__NetBSD__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
+#if defined(__NetBSD__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__sgi)
 /*
  * They have the declaration of vasprintf in stdio.h
  */
