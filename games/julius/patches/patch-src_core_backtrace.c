$NetBSD$

IRIX has no <execinfo.h>.

--- src/core/backtrace.c.orig
+++ src/core/backtrace.c
@@ -4,7 +4,7 @@
 
 #if defined(__GNUC__) && !defined(__MINGW32__) && !defined(__OpenBSD__) && \
     !defined(__vita__) && !defined(__SWITCH__) && !defined(__ANDROID__) && \
-    !defined(__HAIKU__) && !defined(__EMSCRIPTEN__)
+    !defined(__HAIKU__) && !defined(__EMSCRIPTEN__) && !defined(__sgi)
 
 #include <execinfo.h>
 
