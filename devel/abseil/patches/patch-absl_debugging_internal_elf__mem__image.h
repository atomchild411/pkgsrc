$NetBSD$

IRIX has no <link.h>; no ELF memory image there, as on Solaris.

--- absl/debugging/internal/elf_mem_image.h.orig	2026-10-02 18:10:27.038698731 +0000
+++ absl/debugging/internal/elf_mem_image.h	2026-10-02 18:10:27.042698796 +0000
@@ -34,7 +34,8 @@
 
 #if defined(__ELF__) && !defined(__OpenBSD__) && !defined(__QNX__) &&    \
     !defined(__asmjs__) && !defined(__wasm__) && !defined(__HAIKU__) &&  \
-    !defined(__sun) && !defined(__VXWORKS__) && !defined(__hexagon__) && \
+    !defined(__sun) && !defined(__sgi) && !defined(__VXWORKS__) && \
+    !defined(__hexagon__) && \
     !defined(__XTENSA__)
 #define ABSL_HAVE_ELF_MEM_IMAGE 1
 #endif
