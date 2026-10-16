$NetBSD$

thread_time() uses CLOCK_THREAD_CPUTIME_ID: test for it, not for
CLOCK_PROCESS_CPUTIME_ID (IRIX has only the latter), as 3.12 does.

--- Modules/timemodule.c.orig
+++ Modules/timemodule.c
@@ -1480,7 +1480,7 @@
 }
 
 #elif defined(HAVE_CLOCK_GETTIME) && \
-      defined(CLOCK_PROCESS_CPUTIME_ID) && \
+      defined(CLOCK_THREAD_CPUTIME_ID) && \
       !defined(__EMSCRIPTEN__) && !defined(__wasi__)
 #define HAVE_THREAD_TIME
 
