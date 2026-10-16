$NetBSD$

IRIX has no tm_gmtoff; use altzone/timezone as on Solaris.

--- runtime/datetime.c.orig
+++ runtime/datetime.c
@@ -131,8 +131,8 @@ timeval2syslogTime(struct timeval *tp, s
 		t->OffsetMode = '+';
 		lBias = 0;
 	} else {
-#		if defined(__sun)
-			/* Solaris uses a different method of exporting the time zone.
+#		if defined(__sun) || defined(__sgi)
+			/* Solaris (and IRIX) uses a different method of exporting the time zone.
 			 * It is UTC - localtime, which is the opposite sign of mins east of GMT.
 			 */
 			lBias = -(tm->tm_isdst ? altzone : timezone);
