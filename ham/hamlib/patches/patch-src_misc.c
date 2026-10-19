$NetBSD$

IRIX has no tm_gmtoff: use SVR4 timezone/altzone (seconds west).

--- src/misc.c.orig
+++ src/misc.c
@@ -2874,6 +2874,9 @@
         mytm = localtime_r(&t, &result);
 #if defined(_WIN32)
         mytimezone = timezone;
+#elif defined(__sgi)
+        /* no tm_gmtoff: SVR4's seconds west, altzone under DST */
+        mytimezone = result.tm_isdst > 0 ? (int)altzone : (int)timezone;
 #else
         mytimezone = - (int)result.tm_gmtoff; // does not compile on mingw
 #endif
