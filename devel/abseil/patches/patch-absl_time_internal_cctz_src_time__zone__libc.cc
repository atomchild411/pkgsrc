$NetBSD$

IRIX has no tm_gmtoff or tm_zone; use timezone, altzone and tzname like Solaris.

--- absl/time/internal/cctz/src/time_zone_libc.cc.orig
+++ absl/time/internal/cctz/src/time_zone_libc.cc
@@ -50,7 +50,7 @@
   const bool is_dst = tm.tm_isdst > 0;
   return _tzname[is_dst];
 }
-#elif defined(__sun) || defined(_AIX)
+#elif defined(__sun) || defined(_AIX) || defined(__sgi)
 // Uses the globals: 'timezone', 'altzone' and 'tzname'.
 auto tm_gmtoff(const std::tm& tm) -> decltype(timezone) {
   const bool is_dst = tm.tm_isdst > 0;
