$NetBSD$

IRIX has no malloc_usable_size: keep the size ourselves, as on Solaris.

--- src/m_alloc.cpp.orig
+++ src/m_alloc.cpp
@@ -51,7 +51,7 @@
 #endif
 #if defined(__APPLE__)
 #define _msize(p)				malloc_size(p)
-#elif defined(__sun) || defined(__ANDROID__) || defined(__QNX__)
+#elif defined(__sun) || defined(__ANDROID__) || defined(__QNX__) || defined(__sgi)
 #define _msize(p)				(*((size_t*)(p)-1))
 #define OWN_ADDED_SIZE 1
 #elif !defined(_WIN32)
