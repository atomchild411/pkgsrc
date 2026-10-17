$NetBSD$

Only where there is a per-thread CPU clock (not IRIX).

--- abc/src/misc/util/abc_global.h.orig
+++ abc/src/misc/util/abc_global.h
@@ -356,7 +356,7 @@
 #else
   #define APPLE_MACH 0
 #endif
-#if (defined(LIN) || defined(LIN64)) && !APPLE_MACH && !defined(__MINGW32__) && !defined(__wasm)
+#if (defined(LIN) || defined(LIN64)) && !APPLE_MACH && !defined(__MINGW32__) && !defined(__wasm) && defined(CLOCK_THREAD_CPUTIME_ID)
     struct timespec ts;
     if ( clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) < 0 ) 
         return (abctime)-1;
