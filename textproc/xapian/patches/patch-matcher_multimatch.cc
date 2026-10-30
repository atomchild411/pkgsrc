$NetBSD$

IRIX: timer_create() takes no CLOCK_MONOTONIC; use CLOCK_REALTIME.

--- matcher/multimatch.cc.orig
+++ matcher/multimatch.cc
@@ -99,6 +99,10 @@
 //
 // So CLOCK_MONOTONIC is defined, but not supported by timer_create().
 const clockid_t TIMEOUT_CLOCK = CLOCK_REALTIME;
+#elif defined __sgi
+// IRIX's timer_create() has no CLOCK_MONOTONIC: the compiler's covers only
+// clock_gettime() and clock_getres(). The timer here is relative.
+const clockid_t TIMEOUT_CLOCK = CLOCK_REALTIME;
 #else
 const clockid_t TIMEOUT_CLOCK = CLOCK_MONOTONIC;
 #endif
