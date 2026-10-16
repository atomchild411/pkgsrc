$NetBSD: patch-date__parse.c,v 1.1 2025/02/14 08:07:18 vins Exp $

Field `tm_gmtoff' is a BSD extension.

On IRIX use timezone/altzone, following the current DST state.

--- date_parse.c.orig
+++ date_parse.c
@@ -117,7 +117,12 @@ date_parse( char* str )
     ** non-portability, and it's only used for local times that don't
     ** specify a zone - those don't occur in email and netnews.
     */
-#ifdef OS_SYSV
+#if defined(__sgi)
+    /* IRIX: timezone/altzone are seconds west of UTC; like tm_gmtoff
+    ** this follows the current DST state. */
+    tzset();
+    gmtoff = -( now_tmP->tm_isdst > 0 ? altzone : timezone );
+#elif defined(OS_SYSV) || defined(__sun)
     tzset();
     gmtoff = -timezone;
 #else /* OS_SYSV */
