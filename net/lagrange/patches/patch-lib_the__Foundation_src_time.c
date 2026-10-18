$NetBSD$

IRIX: no d_type, st_mtimespec or tm_gmtoff.

--- lib/the_Foundation/src/time.c.orig
+++ lib/the_Foundation/src/time.c
@@ -38,7 +38,7 @@
     tm->tm_min   = date->minute;
     tm->tm_sec   = date->second;
     tm->tm_isdst = date->isDST ? 1 : 0;
-#if !defined (iPlatformWindows) // we only know about daylight savings time
+#if !defined (iPlatformWindows) && !defined (__sgi) // we only know about daylight savings time
     tm->tm_gmtoff = date->gmtOffsetSeconds;
 #endif
     return mktime(tm);
@@ -139,7 +139,7 @@
     d->second           = (short)t->tm_sec;
     d->nsecs            = 0;
     d->isDST            = t->tm_isdst == 1;
-#if !defined (iPlatformWindows)
+#if !defined (iPlatformWindows) && !defined (__sgi) /* IRIX: no tm_gmtoff */
     d->gmtOffsetSeconds = t->tm_gmtoff;
 #else
     d->gmtOffsetSeconds = 0;
@@ -150,6 +150,9 @@
     struct tm t;
     localtime_r(&seconds, &t);
     initStdTime_Date(d, &t);
+#if defined (__sgi)
+    d->gmtOffsetSeconds = -(t.tm_isdst > 0 ? altzone : timezone);
+#endif
 }
 
 void init_Date(iDate *d, const iTime *time) {
