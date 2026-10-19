$NetBSD$

IRIX: pid_t is long, so declare the hooks with it; no d_type in struct dirent; no tm_zone or tm_gmtoff in struct tm.

--- mail-time.c.orig
+++ mail-time.c
@@ -70,9 +70,15 @@
 	tm = localtime(&t);
 
 	/* And work out the timezone. */
+#ifdef __sgi	/* no tm_zone, tm_gmtoff: SVR4's tzname, timezone, altzone */
+	if (strcmp(tz, tzname[tm->tm_isdst > 0]) != 0)
+		goto error;
+	*off = -(tm->tm_isdst > 0 ? altzone : timezone);
+#else
 	if (strcmp(tz, tm->tm_zone) != 0)
 		goto error;
 	*off = tm->tm_gmtoff;
+#endif
 
 	/* Restore the old timezone. */
 	if (saved_tz != NULL) {
