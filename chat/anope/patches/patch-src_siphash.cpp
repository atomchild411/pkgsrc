$NetBSD$

IRIX is always big endian: _le64toh swaps.

--- src/siphash.cpp.orig
+++ src/siphash.cpp
@@ -65,6 +65,11 @@
 #  define _le64toh(x) le64toh(x)
 #endif
 
+// IRIX is always big endian.
+#ifdef __sgi
+#  define _le64toh(x) __builtin_bswap64(x)
+#endif
+
 // Windows is always little endian.
 #ifdef _WIN32
 #  define _le64toh(x) ((uint64_t)(x))
