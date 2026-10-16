$NetBSD$

IRIX has no pthread_condattr_setclock(): the condvar waits on the wall
clock, and the monotonic deadline is turned into a wall-clock one at each
wait (as macOS, which waits relative).

--- src/kj/mutex.c++.orig
+++ src/kj/mutex.c++
@@ -978,7 +978,7 @@
     KJ_PTHREAD_CLEANUP(pthread_cond_destroy(&waiter.condvar));
   });
 
-#if !__APPLE__
+#if !__APPLE__ && !defined(__sgi)
   if (timeout != nullptr) {
     // Oops, the default condvar uses the wall clock, which is dumb... fix it to use the monotonic
     // clock. (Except not on macOS, where pthread_condattr_setclock() is unimplemented, but there's
@@ -1017,6 +1017,14 @@
       // require recomputing the time every iteration...
       struct timespec ts = toRelativeTimespec(kj::max(toTimePoint(*t) - now(), 0 * kj::SECONDS));
       int error = pthread_cond_timedwait_relative_np(&waiter.condvar, &waiter.stupidMutex, &ts);
+#elif defined(__sgi)
+      // IRIX has no pthread_condattr_setclock(): the condvar waits on the wall
+      // clock, so the monotonic deadline becomes a wall-clock one each time.
+      struct timespec rt;
+      KJ_SYSCALL(clock_gettime(CLOCK_REALTIME, &rt));
+      struct timespec ts = toAbsoluteTimespec(
+          toTimePoint(rt) + kj::max(toTimePoint(*t) - now(), 0 * kj::SECONDS));
+      int error = pthread_cond_timedwait(&waiter.condvar, &waiter.stupidMutex, &ts);
 #else
       int error = pthread_cond_timedwait(&waiter.condvar, &waiter.stupidMutex, t);
 #endif
