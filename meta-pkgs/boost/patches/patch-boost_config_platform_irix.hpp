$NetBSD$

The threads limit is old gcc's, not clang's (which also defines __GNUC__):
without threads, Boost.Container picked its Windows mutex.

--- boost/config/platform/irix.hpp.orig	2026-10-02 16:51:34.531081176 +0000
+++ boost/config/platform/irix.hpp	2026-10-02 16:51:34.535081248 +0000
@@ -18,7 +18,7 @@
 #define BOOST_HAS_GETTIMEOFDAY
 #define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
 
-#ifdef __GNUC__
+#if defined(__GNUC__) && !defined(__clang__)
    // GNU C on IRIX does not support threads (checked up to gcc 3.3)
 #  define BOOST_DISABLE_THREADS
 #endif
