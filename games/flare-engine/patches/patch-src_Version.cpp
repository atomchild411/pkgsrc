$NetBSD$

IRIX's <sys/param.h> has MIN and MAX macros, which VersionInfo::MIN(...) and MAX(...) invoked.

--- src/Version.cpp.orig
+++ src/Version.cpp
@@ -30,6 +30,10 @@
 
 #include <SDL.h>
 
+/* IRIX's <sys/param.h> (through SDL) has MIN and MAX macros. */
+#undef MIN
+#undef MAX
+
 Version VersionInfo::ENGINE(1, 12, 0);
 Version VersionInfo::MIN(0, 0, 0);
 Version VersionInfo::MAX(USHRT_MAX, USHRT_MAX, USHRT_MAX);
