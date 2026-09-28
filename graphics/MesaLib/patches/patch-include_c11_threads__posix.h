$NetBSD$

IRIX has no pthread_mutex_timedlock.

--- include/c11/threads_posix.h.orig
+++ include/c11/threads_posix.h
@@ -43,7 +43,7 @@
     Use pthread_mutex_timedlock() for `mtx_timedlock()'
     Otherwise use mtx_trylock() + *busy loop* emulation.
 */
-#if !defined(__CYGWIN__) && !defined(__APPLE__) && !defined(__NetBSD__)
+#if !defined(__CYGWIN__) && !defined(__APPLE__) && !defined(__NetBSD__) && !defined(__sgi)
 #define EMULATED_THREADS_USE_NATIVE_TIMEDLOCK
 #endif
 
