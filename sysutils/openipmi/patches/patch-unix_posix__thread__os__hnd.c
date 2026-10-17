$NetBSD$

IRIX: no pthread_condattr_setclock; wait for the relative time instead.

--- unix/posix_thread_os_hnd.c.orig
+++ unix/posix_thread_os_hnd.c
@@ -476,11 +476,13 @@
     if (rv)
 	return rv;
 
+#ifndef __sgi
     rv = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
     if (rv) {
 	pthread_condattr_destroy(&attr);
 	return rv;
     }
+#endif
 
     cond = malloc(sizeof(*cond));
     if (!cond) {
@@ -533,6 +535,13 @@
     struct timeval  now;
     int             rv;
 
+#ifdef __sgi
+    /* IRIX has no pthread_condattr_setclock: wait for the relative time. */
+    spec.tv_sec = timeout->tv_sec + timeout->tv_usec / 1000000;
+    spec.tv_nsec = (timeout->tv_usec % 1000000) * 1000;
+    return pthread_cond_timedwait_relative_np(&cond->cond, &lock->mutex,
+					      &spec);
+#endif
     rv = handler->get_monotonic_time(handler, &now);
     if (rv)
 	return rv;
