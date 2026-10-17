$NetBSD: patch-pdns_misc.hh,v 1.3 2025/06/30 11:00:50 jperkin Exp $

Checking for CLOCK_THREAD_CPUTIME_ID is sufficient, not all systems
define _POSIX_THREAD_CPUTIME.
CPUTime on the process's CPU clock where there is none per thread (IRIX).

--- pdns/misc.hh.orig
+++ pdns/misc.hh
@@ -209,19 +209,25 @@
 void dropPrivs(int uid, int gid);
 void cleanSlashes(string &str);
 
-#if defined(_POSIX_THREAD_CPUTIME) && defined(CLOCK_THREAD_CPUTIME_ID)
+#if defined(CLOCK_THREAD_CPUTIME_ID)
+#define PDNS_CPUTIME_CLOCK CLOCK_THREAD_CPUTIME_ID
+#elif defined(CLOCK_PROCESS_CPUTIME_ID)
+/* No CPU time per thread (IRIX): the process's. */
+#define PDNS_CPUTIME_CLOCK CLOCK_PROCESS_CPUTIME_ID
+#endif
+#ifdef PDNS_CPUTIME_CLOCK
 /** CPUTime measurements */
 class CPUTime
 {
 public:
   void start()
   {
-    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &d_start);
+    clock_gettime(PDNS_CPUTIME_CLOCK, &d_start);
   }
   uint64_t ndiff()
   {
     struct timespec now;
-    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &now);
+    clock_gettime(PDNS_CPUTIME_CLOCK, &now);
     return 1000000000ULL*(now.tv_sec - d_start.tv_sec) + (now.tv_nsec - d_start.tv_nsec);
   }
 private:
