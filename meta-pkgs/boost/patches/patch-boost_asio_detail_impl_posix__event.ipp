$NetBSD$

IRIX has no pthread_condattr_setclock: its condition variables time out by the realtime clock (posix_event.hpp).

--- boost/asio/detail/impl/posix_event.ipp.orig
+++ boost/asio/detail/impl/posix_event.ipp
@@ -33,7 +33,7 @@
 posix_event::posix_event()
   : state_(0)
 {
-#if (defined(__MACH__) && defined(__APPLE__)) \
+#if defined(__sgi) || (defined(__MACH__) && defined(__APPLE__)) \
       || (defined(__ANDROID__) && (__ANDROID_API__ < 21))
   int error = ::pthread_cond_init(&cond_, 0);
 #else // (defined(__MACH__) && defined(__APPLE__))
