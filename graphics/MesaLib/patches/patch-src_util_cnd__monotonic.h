$NetBSD$

IRIX condition variables only take CLOCK_REALTIME deadlines: wait
relatively (pthread_cond_timedwait_relative_np).

--- src/util/cnd_monotonic.h.orig
+++ src/util/cnd_monotonic.h
@@ -56,8 +56,14 @@
    int ret = thrd_error;
    pthread_condattr_t condattr;
    if (pthread_condattr_init(&condattr) == 0) {
+#ifdef __sgi
+      /* IRIX condition variables only take CLOCK_REALTIME deadlines: keep
+       * the default and wait relatively (u_cnd_monotonic_timedwait). */
+      if (pthread_cond_init(&cond->cond, &condattr) == 0) {
+#else
       if ((pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC) == 0) &&
          (pthread_cond_init(&cond->cond, &condattr) == 0)) {
+#endif
          ret = thrd_success;
       }
 
@@ -120,6 +126,18 @@
    if (SleepConditionVariableCS(&cond->condvar, mtx, timeout))
       return thrd_success;
    return (GetLastError() == ERROR_TIMEOUT) ? thrd_busy : thrd_error;
+#elif defined(__sgi)
+   int64_t rel = (int64_t)abs_time->tv_sec * 1000000000 + abs_time->tv_nsec -
+                 os_time_get_nano();
+   struct timespec ts;
+   if (rel < 0)
+      rel = 0;
+   ts.tv_sec = rel / 1000000000;
+   ts.tv_nsec = rel % 1000000000;
+   int rt = pthread_cond_timedwait_relative_np(&cond->cond, mtx, &ts);
+   if (rt == ETIMEDOUT)
+      return thrd_busy;
+   return (rt == 0) ? thrd_success : thrd_error;
 #else
    int rt = pthread_cond_timedwait(&cond->cond, mtx, abs_time);
    if (rt == ETIMEDOUT)
