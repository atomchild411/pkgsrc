$NetBSD$

IRIX: big-endian MIPS (_MIPSEB).

--- src/util/u_endian.h.orig
+++ src/util/u_endian.h
@@ -82,6 +82,16 @@
 # define UTIL_ARCH_BIG_ENDIAN 1
 #endif
 
+#elif defined(__sgi)
+
+#if defined(_MIPSEB)
+# define UTIL_ARCH_LITTLE_ENDIAN 0
+# define UTIL_ARCH_BIG_ENDIAN 1
+#else
+# define UTIL_ARCH_LITTLE_ENDIAN 1
+# define UTIL_ARCH_BIG_ENDIAN 0
+#endif
+
 #elif defined(_WIN32) || defined(ANDROID)
 
 #define UTIL_ARCH_LITTLE_ENDIAN 1
