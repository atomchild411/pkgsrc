$NetBSD$

IRIX: timer_create() takes no CLOCK_MONOTONIC (E1286); use CLOCK_REALTIME.

--- src/os_unix.c.orig
+++ src/os_unix.c
@@ -9003,7 +9003,13 @@
 
 	action.sigev_notify = SIGEV_THREAD;
 	action.sigev_notify_function = set_flag;
+#  ifdef __sgi
+	// IRIX's timer_create() has no CLOCK_MONOTONIC (the compiler's covers
+	// only clock_gettime() and clock_getres()); the timeout is relative.
+	ret = timer_create(CLOCK_REALTIME, &action, &timer_id);
+#  else
 	ret = timer_create(CLOCK_MONOTONIC, &action, &timer_id);
+#  endif
 	if (ret < 0)
 	{
 	    semsg(_(e_could_not_set_timeout_str), strerror(errno));
