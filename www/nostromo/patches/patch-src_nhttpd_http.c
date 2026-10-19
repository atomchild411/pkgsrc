$NetBSD$

IRIX: no tm_zone or tm_gmtoff; tzname, altzone and timezone.

--- src/nhttpd/http.c.orig
+++ src/nhttpd/http.c
@@ -1280,7 +1280,11 @@
 
 	snprintf(date, sizeof(date), "%s, %02d %s %d %02d:%02d:%02d %s",
 	    day[t->tm_wday], t->tm_mday, month[t->tm_mon], t->tm_year + 1900,
+#ifdef __sgi	/* no tm_zone */
+	    t->tm_hour, t->tm_min, t->tm_sec, tzname[t->tm_isdst > 0]);
+#else
 	    t->tm_hour, t->tm_min, t->tm_sec, t->tm_zone);
+#endif
 
 	return (date);
 }
