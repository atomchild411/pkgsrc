$NetBSD$

IRIX has mmap(2): without ABSL_HAVE_MMAP, LowLevelAlloc and everything
built on it (PerThreadSem, CreateThreadIdentity) were compiled out, and
libabsl_synchronization referenced them undefined.

--- absl/base/config.h.orig
+++ absl/base/config.h
@@ -379,7 +379,7 @@
     defined(__EMSCRIPTEN__) || defined(__Fuchsia__) || defined(__sun) ||  \
     defined(__myriad2__) || defined(__HAIKU__) || defined(__OpenBSD__) || \
     defined(__NetBSD__) || defined(__QNX__) || defined(__VXWORKS__) ||    \
-    defined(__hexagon__) || defined(__XTENSA__) ||                        \
+    defined(__hexagon__) || defined(__XTENSA__) || defined(__sgi) ||      \
     defined(_WASI_EMULATED_MMAN)
 #define ABSL_HAVE_MMAP 1
 #endif
