$NetBSD$

IRIX 6.5 has usleep().

--- config.h.orig
+++ config.h
@@ -95,7 +95,7 @@
 #   define SYSV_SIGNALS
 #   define USE_SIGNALS
 #   define my_ioperm(x,y,z) 0
-#   define USE_BOGUS_USLEEP
+/* IRIX 6.5 has usleep(). */
 #   define PROCESSOR_SPEED 33
 #   define STRERROR_DEF_MISSING
 #endif
