$NetBSD: patch-src_quickjs_quickjs.c,v 1.2 2025/10/31 21:46:23 adam Exp $

Add support for NetBSD.
IRIX: no malloc_usable_size (as for EMSCRIPTEN), no tm_gmtoff, and <unistd.h> declares crypt().

--- src/quickjs/quickjs.c.orig
+++ src/quickjs/quickjs.c
@@ -36,7 +36,7 @@
 #include <math.h>
 #if defined(__APPLE__)
 #include <malloc/malloc.h>
-#elif defined(__linux__) || defined(__NX__)
+#elif defined(__linux__) || defined(__NX__) || defined(__NetBSD__)
 #include <malloc.h>
 #elif defined(__FreeBSD__)
 #include <malloc_np.h>
@@ -1702,7 +1702,7 @@
     return malloc_size(ptr);
 #elif defined(_WIN32)
     return _msize(ptr);
-#elif defined(EMSCRIPTEN)
+#elif defined(EMSCRIPTEN) || defined(__sgi)
     return 0;
 #elif defined(__linux__) || defined(__NX__)
     return malloc_usable_size(ptr);
@@ -1776,7 +1776,7 @@
     malloc_size,
 #elif defined(_WIN32)
     (size_t (*)(const void *))_msize,
-#elif defined(EMSCRIPTEN)
+#elif defined(EMSCRIPTEN) || defined(__sgi)
     NULL,
 #elif defined(__linux__) || defined(__NX__)
     (size_t (*)(const void *))malloc_usable_size,
@@ -42184,8 +42184,13 @@
     }
     ti = time;
     localtime_r(&ti, &tm);
+#ifdef __sgi	/* no tm_gmtoff: SVR4's timezone and altzone */
+    tzset();
+    return (tm.tm_isdst > 0 ? altzone : timezone) / 60;
+#else
     return -tm.tm_gmtoff / 60;
 #endif
+#endif
 }
 
 #if 0
