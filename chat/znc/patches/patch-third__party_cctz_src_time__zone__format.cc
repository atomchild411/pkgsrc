$NetBSD$

IRIX: _XOPEN_SOURCE (XPG4) hides struct timespec, which libc++ needs (strptime is visible without it); no tm_gmtoff/tm_zone in struct tm.

--- third_party/cctz/src/time_zone_format.cc.orig
+++ third_party/cctz/src/time_zone_format.cc
@@ -19,7 +19,7 @@
 #endif
 
 #if defined(HAS_STRPTIME) && HAS_STRPTIME
-# if !defined(_XOPEN_SOURCE) && !defined(__OpenBSD__)
+# if !defined(_XOPEN_SOURCE) && !defined(__OpenBSD__) && !defined(__sgi)
 #  define _XOPEN_SOURCE  // Definedness suffices for strptime.
 # endif
 #endif
