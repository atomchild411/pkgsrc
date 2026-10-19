$NetBSD$

IRIX: _XOPEN_SOURCE (XPG4) hides struct timespec, which libc++ needs (strptime is visible without it); no tm_gmtoff/tm_zone in struct tm.

--- third_party/cctz/src/time_zone_libc.cc.orig
+++ third_party/cctz/src/time_zone_libc.cc
@@ -46,6 +46,16 @@
   const bool is_dst = tm.tm_isdst > 0;
   return _tzname[is_dst];
 }
+#elif defined(__sgi)
+// IRIX: no tm_gmtoff; SVR4's 'timezone' and 'altzone' are seconds west.
+auto tm_gmtoff(const std::tm& tm) -> decltype(timezone) {
+  const bool is_dst = tm.tm_isdst > 0;
+  return -(is_dst ? altzone : timezone);
+}
+auto tm_zone(const std::tm& tm) -> decltype(tzname[0]) {
+  const bool is_dst = tm.tm_isdst > 0;
+  return tzname[is_dst];
+}
 #elif defined(__sun) || defined(_AIX)
 // Uses the globals: 'timezone', 'altzone' and 'tzname'.
 auto tm_gmtoff(const std::tm& tm) -> decltype(timezone) {
