$NetBSD: patch-src_utils_NumberUtils.h,v 1.2 2023/11/09 15:21:17 nros Exp $

Solaris does not have strtod_l and strtof_l
Portability fix, use "defined" to check for preprocessor defines
NetBSD has strtol_l
IRIX has neither strtod_l nor strtof_l either.

--- src/utils/NumberUtils.h.orig
+++ src/utils/NumberUtils.h
@@ -125,6 +125,8 @@
     double
 #ifdef _WIN32
     tempval = _strtod_l(first, &endptr, loc.local);
+#elif defined(__sun__) || defined(__sgi)
+    tempval = ::strtod(first, &endptr);
 #else
     tempval = ::strtod_l(first, &endptr, loc.local);
 #endif
@@ -178,9 +180,11 @@
 #else
     tempval = _strtof_l(first, &endptr, loc.local);
 #endif
-#elif __APPLE__
+#elif defined(__APPLE__)
     // On OSX, strtod_l is for some reason drastically faster than strtof_l.
     tempval = static_cast<float>(::strtod_l(first, &endptr, loc.local));
+#elif defined(__sun__) || defined(__sgi)
+    tempval = ::strtof(first, &endptr);
 #else
     tempval = ::strtof_l(first, &endptr, loc.local);
 #endif
@@ -229,7 +233,7 @@
     long int
 #ifdef _WIN32
     tempval = _strtol_l(first, &endptr, 0, loc.local);
-#elif defined(__GLIBC__)
+#elif defined(__GLIBC__) || defined(__NetBSD__)
     tempval = ::strtol_l(first, &endptr, 0, loc.local);
 #else
     tempval = ::strtol(first, &endptr, 0);
