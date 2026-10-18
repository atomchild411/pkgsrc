$NetBSD$

IRIX has no pthread_condattr_setclock(): its condition variables wait by CLOCK_REALTIME.

--- include/asio/detail/impl/posix_event.ipp.orig
+++ include/asio/detail/impl/posix_event.ipp
@@ -32,7 +32,8 @@
   : state_(0)
 {
 #if (defined(__MACH__) && defined(__APPLE__)) \
-      || (defined(__ANDROID__) && (__ANDROID_API__ < 21))
+      || (defined(__ANDROID__) && (__ANDROID_API__ < 21)) \
+      || defined(__sgi) // no pthread_condattr_setclock()
   int error = ::pthread_cond_init(&cond_, 0);
 #else // (defined(__MACH__) && defined(__APPLE__))
       // || (defined(__ANDROID__) && (__ANDROID_API__ < 21))
