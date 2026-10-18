$NetBSD$

IRIX has RLIMIT_RSS but no RLIMIT_MEMLOCK.

--- res/res_limit.c.orig
+++ res/res_limit.c
@@ -52,6 +52,8 @@
 	{ RLIMIT_CORE,    "-c", "core file size", "core" },
 #ifdef RLIMIT_RSS
 	{ RLIMIT_RSS,     "-m", "resident memory", "memory" },
+#endif
+#ifdef RLIMIT_MEMLOCK
 	{ RLIMIT_MEMLOCK, "-l", "amount of memory locked into RAM", "locked" },
 #endif
 #ifdef RLIMIT_NPROC
