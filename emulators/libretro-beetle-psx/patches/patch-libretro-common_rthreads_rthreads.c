$NetBSD: patch-libretro-common_rthreads_rthreads.c,v 1.1 2018/09/07 00:45:24 nia Exp $

FreeBSD needs _POSIX_C_SOURCE=200112L for CLOCK_REALTIME.
IRIX: the __mips__ branch needs <sys/time.h> for gettimeofday().

--- libretro-common/rthreads/rthreads.c.orig
+++ libretro-common/rthreads/rthreads.c
@@ -22,7 +22,7 @@
 
 #ifdef __unix__
 #ifndef __sun__
-#define _POSIX_C_SOURCE 199309
+#define _POSIX_C_SOURCE 200112L
 #endif
 #endif
 
@@ -58,7 +58,7 @@
 #include <time.h>
 #endif
 
-#if defined(VITA) || defined(BSD) || defined(ORBIS)
+#if defined(VITA) || defined(BSD) || defined(ORBIS) || defined(__sgi)
 #include <sys/time.h>
 #endif
 
