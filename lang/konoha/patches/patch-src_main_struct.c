$NetBSD$

IRIX: no tm_gmtoff; use timezone/altzone.

--- src/main/struct.c.orig
+++ src/main/struct.c
@@ -772,6 +772,8 @@
 #if defined(K_USING_MINGW_)
 	_tzset();
 	dt->dt.gmtoff = (kshort_t)(_timezone / (60 * 60));
+#elif defined(__sgi) /* IRIX: no tm_gmtoff */
+	dt->dt.gmtoff = (kshort_t)(-(tm.tm_isdst > 0 ? altzone : timezone) / (60 * 60));
 #else
 	dt->dt.gmtoff = (kshort_t)(tm.tm_gmtoff / (60 * 60));
 #endif /* defined(K_USING_MINGW_) */
