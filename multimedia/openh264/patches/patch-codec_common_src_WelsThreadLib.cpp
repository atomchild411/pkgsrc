$NetBSD: patch-codec_common_src_WelsThreadLib.cpp,v 1.1 2024/11/07 10:48:03 jperkin Exp $

Support illumos and IRIX (no <sys/sysctl.h>; sysconf counts the CPUs).

--- codec/common/src/WelsThreadLib.cpp.orig	2024-11-07 10:13:29.225625539 +0000
+++ codec/common/src/WelsThreadLib.cpp
@@ -50,7 +50,7 @@
 #include <unistd.h>
 #ifdef __EMSCRIPTEN__
 #include <emscripten/threading.h>
-#elif !defined(__Fuchsia__)
+#elif !defined(__Fuchsia__) && !defined(__illumos__) && !defined(__sgi)
 #include <sys/sysctl.h>
 #endif
 #ifdef __APPLE__
@@ -513,7 +513,7 @@ WELS_THREAD_ERROR_CODE    WelsQueryLogic
   pInfo->ProcessorCount = emscripten_num_logical_cores();
   return WELS_THREAD_ERROR_OK;
 
-#elif defined(__Fuchsia__)
+#elif defined(__Fuchsia__) || defined(__illumos__) || defined(__sgi)
 
   pInfo->ProcessorCount = sysconf(_SC_NPROCESSORS_ONLN);
   return WELS_THREAD_ERROR_OK;
