$NetBSD$

IRIX has no pthread barriers: use the Android fallback.

--- libusb/hidapi_thread_pthread.h.orig
+++ libusb/hidapi_thread_pthread.h
@@ -24,7 +24,7 @@
 
 #include <pthread.h>
 
-#if defined(__ANDROID__) && __ANDROID_API__ < __ANDROID_API_N__
+#if (defined(__ANDROID__) && __ANDROID_API__ < __ANDROID_API_N__) || defined(__sgi)
 
 /* Barrier implementation because Android/Bionic don't have pthread_barrier.
    This implementation came from Brent Priddy and was posted on
