$NetBSD$

IRIX: no tm_zone or tm_gmtoff; tzname, altzone and timezone.

--- src/nhttpd/sys.c.orig
+++ src/nhttpd/sys.c
@@ -749,7 +749,11 @@
 	char		*d, sign;
 	static char	date[64];
 
+#ifdef __sgi	/* no tm_gmtoff */
+	diff = -(t->tm_isdst > 0 ? altzone : timezone) / 3600;
+#else
 	diff = t->tm_gmtoff / 3600;
+#endif
 
 	if (diff < 0) {
 		diff = -diff;
