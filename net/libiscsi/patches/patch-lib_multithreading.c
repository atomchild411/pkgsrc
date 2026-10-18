$NetBSD: patch-lib_multithreading.c,v 1.2 2026/09/09 11:58:13 jperkin Exp $

Add thread id retrieval for FreeBSD/DragonFly, OpenBSD and NetBSD.
https://github.com/sahlberg/libiscsi/pull/466
And IRIX (pthread_self()).

--- lib/multithreading.c.orig
+++ lib/multithreading.c
@@ -144,6 +144,15 @@
 #include <signal.h>
 #include <unistd.h>
 #include <sys/syscall.h>
+#if defined(__FreeBSD__) || defined(__DragonFly__)
+#include <pthread_np.h>
+#endif
+#if defined(__NetBSD__)
+#include <lwp.h>
+#endif
+#if defined(__illumos__)
+#include <thread.h>
+#endif
 
 iscsi_tid_t iscsi_mt_get_tid(void)
 {
@@ -151,6 +160,21 @@
         iscsi_tid_t tid;
         pthread_threadid_np(NULL, &tid);
         return tid;
+#elif defined(__FreeBSD__) || defined(__DragonFly__)
+        int tid = pthread_getthreadid_np();
+        return tid;
+#elif defined(__OpenBSD__)
+        pid_t tid = getthrid();
+        return tid;
+#elif defined(__NetBSD__)
+        lwpid_t tid = _lwp_self();
+        return tid;
+#elif defined(__illumos__)
+	thread_t tid = thr_self();
+	return tid;
+#elif defined(__sgi)
+        /* IRIX's pthread_t is the thread's integer id */
+        return (iscsi_tid_t)pthread_self();
 #elif defined(SYS_gettid)
         pid_t tid = syscall(SYS_gettid);
         return tid;
