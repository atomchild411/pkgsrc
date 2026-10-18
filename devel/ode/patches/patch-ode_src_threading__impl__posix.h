$NetBSD$

Without pthread_condattr_setclock() (IRIX), condvars wait by CLOCK_REALTIME.

--- ode/src/threading_impl_posix.h.orig
+++ ode/src/threading_impl_posix.h
@@ -105,7 +105,14 @@
 
 #else // #if !HAVE_PTHREAD_CONDATTR_SETCLOCK
 
-#error It is necessary to check manuals for the correct way of getting condvar wait time for this system
+// No pthread_condattr_setclock() (IRIX): the condvar waits by CLOCK_REALTIME,
+// whatever clock the caller names.
+static inline 
+int _condvar_clock_gettime(int clock_type, timespec *ts)
+{
+    (void)clock_type; // Unused
+    return clock_gettime(CLOCK_REALTIME, ts);
+}
 
 
 #endif // #if !HAVE_PTHREAD_CONDATTR_SETCLOCK
