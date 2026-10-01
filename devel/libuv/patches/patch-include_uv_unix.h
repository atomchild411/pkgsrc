$NetBSD$

IRIX uses the POSIX platform header.

--- include/uv/unix.h.orig
+++ include/uv/unix.h
@@ -66,7 +66,8 @@
       defined(__MSYS__)   || \
       defined(__HAIKU__)  || \
       defined(__QNX__)    || \
-      defined(__GNU__)
+      defined(__GNU__)    || \
+      defined(__sgi)
 # include "uv/posix.h"
 #endif
 
