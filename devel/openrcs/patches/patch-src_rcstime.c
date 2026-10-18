$NetBSD$

IRIX: no d_type in struct dirent (stat instead); no tm_gmtoff in struct tm.

--- src/rcstime.c.orig
+++ src/rcstime.c
@@ -42,7 +42,12 @@
 	if (!strcmp(tz, "LT")) {
 		now = mktime(&rdp->rd_date);
 		ltb = localtime(&now);
+#ifdef __sgi
+		/* No tm_gmtoff on IRIX. */
+		ltb->tm_hour += ((int)(ltb->tm_isdst > 0 ? -altzone : -timezone)/3600);
+#else
 		ltb->tm_hour += ((int)ltb->tm_gmtoff/3600);
+#endif
 		memcpy(tb, ltb, sizeof(*tb));
 	} else {
 		pos = 0;
@@ -68,10 +73,14 @@
 
 		if (pos) {
 			tb->tm_hour += tzone;
+#ifndef __sgi
 			tb->tm_gmtoff += (tzone * 3600);
+#endif
 		} else {
 			tb->tm_hour -= tzone;
+#ifndef __sgi
 			tb->tm_gmtoff -= (tzone * 3600);
+#endif
 		}
 
 		if ((tb->tm_hour >= 24) || (tb->tm_hour <= -24))
@@ -88,7 +97,9 @@
 			} else
 				tb->tm_min += tzone;
 
+#ifndef __sgi
 			tb->tm_gmtoff += (tzone*60);
+#endif
 		}
 	}
 }
