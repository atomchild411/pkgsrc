$NetBSD$

IRIX: no tm_gmtoff; the offset from timezone.

--- src/conf.c.orig
+++ src/conf.c
@@ -131,7 +131,12 @@
     time_t t = time(NULL);
     struct tm * lt = localtime(&t);
     char strgmtoff[7];
+#ifdef __sgi
+    /* No tm_gmtoff on IRIX (and altzone needs SGI mode). */
+    sprintf(strgmtoff, "%ld", (long) ((lt->tm_isdst > 0 ? 3600 : 0) - timezone));
+#else
     sprintf(strgmtoff, "%ld", lt->tm_gmtoff);
+#endif
     put(user_conf_d, "tm_gmtoff", strgmtoff);
 #endif
 }
