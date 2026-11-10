$NetBSD$

IRIX: the main loop's code for systems without pselect(). IRIX has none;
the toolchain's stand-in is not atomic, and IRIX restarts select() after
the SA_RESTART SIGALRM and SIGCHLD handlers here, so with no timeout the
loop slept on past timers and child exits until the next X event. The
other path bounds the wait when timers are pending.

--- libmainloop/select.c.orig
+++ libmainloop/select.c
@@ -103,7 +103,7 @@
     int ret=0;
 
 
-#if _POSIX_SELECT || _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
+#if (_POSIX_SELECT || _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !defined(__sgi)
     {
         sigset_t oldmask;
 
