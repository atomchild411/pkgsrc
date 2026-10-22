$NetBSD$

IRIX: condition variables have no clock attribute (no pthread_condattr_setclock); keep the realtime clock.

--- libs/atomic/src/lock_pool.cpp.orig
+++ libs/atomic/src/lock_pool.cpp
@@ -62,6 +62,12 @@
 #else // BOOST_OS_WINDOWS
 #include <time.h>
 #include <unistd.h> // _POSIX_MONOTONIC_CLOCK
+#if defined(__sgi)
+// IRIX: condition variables have no clock attribute (no
+// pthread_condattr_setclock); their timed waits are on CLOCK_REALTIME, so
+// take the paths for systems without a monotonic clock.
+#undef _POSIX_MONOTONIC_CLOCK
+#endif
 #include <cerrno>
 #include <boost/atomic/detail/futex.hpp>
 #if defined(BOOST_ATOMIC_DETAIL_HAS_FUTEX) && BOOST_ATOMIC_INT32_LOCK_FREE == 2
