$NetBSD: patch-src_supertux_error__handler.cpp,v 1.1 2026/03/31 10:47:13 adam Exp $

Fix build.
No stack trace on IRIX: it has no <execinfo.h>.

--- src/supertux/error_handler.cpp.orig
+++ src/supertux/error_handler.cpp
@@ -33,7 +33,7 @@
 
 #include "util/file_system.hpp"
 
-#if (defined(__unix__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__)) && !(defined(__EMSCRIPTEN__) || defined(__ANDROID__))
+#if (defined(__unix__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__)) && !(defined(__EMSCRIPTEN__) || defined(__ANDROID__) || defined(__sgi))
 #define UNIX
 #endif
 
@@ -69,7 +69,7 @@
 static PCONTEXT pcontext = NULL;
 #endif
 
-#ifdef _GNU_SOURCE
+#ifdef __GLIBCXX__
 # include <cxxabi.h>
 #endif
 
