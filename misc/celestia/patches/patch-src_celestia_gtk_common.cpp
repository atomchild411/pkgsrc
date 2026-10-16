$NetBSD$

IRIX struct tm has no tm_gmtoff; use the timezone/altzone globals.

--- src/celestia/gtk/common.cpp.orig
+++ src/celestia/gtk/common.cpp
@@ -33,8 +33,13 @@ gint tzOffsetAtDate(astro::Date date)
 	time_t time = (time_t)astro::julianDateToSeconds(date - astro::Date(1970, 1, 1));
 	struct tm *d = localtime(&time);
 	
+	#ifdef __sgi
+	/* IRIX has no tm_gmtoff; timezone/altzone are seconds west of UTC */
+	return (gint)-(d->tm_isdst > 0 ? altzone : timezone);
+	#else
 	return (gint)d->tm_gmtoff;
 	#endif
+	#endif
 }
 
 
