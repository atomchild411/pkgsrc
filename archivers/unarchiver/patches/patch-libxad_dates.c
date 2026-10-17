$NetBSD$

IRIX has no tm_gmtoff: the offset from the time and the same broken-down
UTC time read back with mktime.

--- libxad/dates.c.orig
+++ libxad/dates.c
@@ -328,7 +328,16 @@
   {
     time_t t = time(NULL);
     struct tm *tm = localtime(&t);
+#if defined(__sgi)
+    /* No tm_gmtoff: the difference between the time and the same broken-down
+       UTC time read as local time. */
+    int isdst = tm->tm_isdst; /* before gmtime, which may share tm */
+    struct tm g = *gmtime(&t);
+    g.tm_isdst = isdst;
+    gmtoffs = (long)difftime(t, mktime(&g))/60;
+#else
     gmtoffs = tm->tm_gmtoff/60;
+#endif
   }
 #else
   gmttst=0;
