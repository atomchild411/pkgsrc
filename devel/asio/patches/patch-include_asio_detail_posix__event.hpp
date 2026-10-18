$NetBSD$

IRIX has no pthread_condattr_setclock(): its condition variables wait by CLOCK_REALTIME.

--- include/asio/detail/posix_event.hpp.orig
+++ include/asio/detail/posix_event.hpp
@@ -139,7 +139,12 @@
 #else // (defined(__MACH__) && defined(__APPLE__))
       // || (defined(__ANDROID__) && (__ANDROID_API__ < 21)
       //     && defined(HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE))
+#if defined(__sgi)
+      // The condition variable waits by CLOCK_REALTIME (no setclock).
+      if (::clock_gettime(CLOCK_REALTIME, &ts) == 0)
+#else
       if (::clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
+#endif
       {
         ts.tv_sec += usec / 1000000;
         ts.tv_nsec += (usec % 1000000) * 1000;
