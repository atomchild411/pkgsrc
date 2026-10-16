$NetBSD$

thread_time() uses CLOCK_THREAD_CPUTIME_ID: test for it, not for
CLOCK_PROCESS_CPUTIME_ID (IRIX has only the latter), as 3.12 does.

--- Modules/timemodule.c.orig
+++ Modules/timemodule.c
@@ -1453,7 +1453,7 @@
     return 0;
 }
 
-#elif defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_PROCESS_CPUTIME_ID)
+#elif defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_THREAD_CPUTIME_ID)
 #define HAVE_THREAD_TIME
 
 #if defined(__APPLE__) && defined(__has_attribute) && __has_attribute(availability)
