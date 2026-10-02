$NetBSD$

IRIX has no pthread_condattr_setclock(): its condition variables wait on
the realtime clock, so the internal clock must stay that one.

--- boost/thread/detail/config.hpp.orig	2026-10-02 17:06:25.993462662 +0000
+++ boost/thread/detail/config.hpp	2026-10-02 17:06:26.009462876 +0000
@@ -435,7 +435,9 @@
   #include <time.h> // check for CLOCK_MONOTONIC
   #if defined(CLOCK_MONOTONIC)
     #define BOOST_THREAD_HAS_MONO_CLOCK
+    #if !defined(__sgi)
     #define BOOST_THREAD_INTERNAL_CLOCK_IS_MONO
+    #endif
   #endif
 #endif
 
