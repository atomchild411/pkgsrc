$NetBSD: patch-src_util.c,v 1.1 2022/10/30 21:58:30 wiedi Exp $

No tm_gmtoff on SunOS
No tm_gmtoff on IRIX either.

--- src/util.c.orig
+++ src/util.c
@@ -524,7 +524,11 @@
   struct tm tmp;
 
   tmp = *src;
+#if defined(__sun) || defined(__sgi)
+  return timegm (&tmp);
+#else
   return timegm (&tmp) - src->tm_gmtoff;
+#endif
 }
 
 void
