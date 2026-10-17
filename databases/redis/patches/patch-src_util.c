$NetBSD$

IRIX: XPG5 mode (siginfo_t, IOV_MAX), and the XPG timezone variable (its struct timezone is BSD/SGI-only).

--- src/util.c.orig
+++ src/util.c
@@ -1085,7 +1085,7 @@
  * i.e timezone variables are linux specific.
  */
 long getTimeZone(void) {
-#if defined(__linux__) || defined(__sun)
+#if defined(__linux__) || defined(__sun) || defined(__sgi)
     return timezone;
 #else
     struct timezone tz;
