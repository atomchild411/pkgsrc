$NetBSD: patch-src_julian__day.c,v 1.1 2024/06/10 10:50:32 jperkin Exp $

SunOS does not have gmtoff.

IRIX does not have gmtoff either; use its timezone/altzone globals.

--- src/julian_day.c.orig
+++ src/julian_day.c
@@ -298,7 +298,14 @@ void ln_get_local_date (double JD, struc
 #else
  	curtime = time (NULL);
  	loctime = localtime(&curtime);
+#ifdef __sun
+ 	gmtoff = 0;
+#elif defined(__sgi)
+ 	/* IRIX: no tm_gmtoff; timezone/altzone are seconds west of UTC */
+ 	gmtoff = -(loctime->tm_isdst > 0 ? altzone : timezone);
+#else
  	gmtoff = loctime->tm_gmtoff;
+#endif
 	// otherwise there is no reasonable way how to get that:(
 	// tm_gmtoff already included DST
 #endif
