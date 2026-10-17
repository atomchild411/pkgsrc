$NetBSD$

No stack trace on IRIX: it has no <execinfo.h>.

--- src/platform/crash_handler.c.orig
+++ src/platform/crash_handler.c
@@ -6,7 +6,7 @@
 
 #include "SDL.h"
 
-#if (defined(__GNUC__) && !defined(__MINGW32__) && !defined(__OpenBSD__) && \
+#if (defined(__GNUC__) && !defined(__MINGW32__) && !defined(__OpenBSD__) && !defined(__sgi) && \
    !defined(__vita__) && !defined(__SWITCH__) && !defined(__ANDROID__) && \
    !defined(__HAIKU__) && !defined(__EMSCRIPTEN__)) || \
     (defined(_WIN32) && (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM64)))
