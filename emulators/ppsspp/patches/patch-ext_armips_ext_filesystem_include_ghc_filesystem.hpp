$NetBSD$

IRIX is a System V Release 4 too, without __svr4__.

--- ext/armips/ext/filesystem/include/ghc/filesystem.hpp.orig
+++ ext/armips/ext/filesystem/include/ghc/filesystem.hpp
@@ -60,7 +60,7 @@
 #elif defined(_WIN32)
 #define GHC_OS_WINDOWS
 #define GHC_OS_WIN32
-#elif defined(__svr4__)
+#elif defined(__svr4__) || defined(__sgi)
 #define GHC_OS_SYS5R4
 #elif defined(BSD)
 #define GHC_OS_BSD
