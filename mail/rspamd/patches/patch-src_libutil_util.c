$NetBSD$

IRIX: no tm_gmtoff or tm_zone, as on Solaris.

--- src/libutil/util.c.orig
+++ src/libutil/util.c
@@ -2335,7 +2335,7 @@
 	dest->tm_hour = remsecs / 3600;
 	dest->tm_min = remsecs / 60 % 60;
 	dest->tm_sec = remsecs % 60;
-#if !defined(__sun)
+#if !defined(__sun) && !defined(__sgi)
 	dest->tm_gmtoff = 0;
 	dest->tm_zone = "GMT";
 #endif
