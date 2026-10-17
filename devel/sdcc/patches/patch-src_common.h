$NetBSD$

IRIX's <ctype.h> defines _G too (sdcc's files have a static _G).

--- src/common.h.orig
+++ src/common.h
@@ -26,7 +26,7 @@
 #ifndef COMMON_H
 #define COMMON_H
 
-#if defined(__APPLE__) && (__MACH__)
+#if (defined(__APPLE__) && (__MACH__)) || defined(__sgi)
 #ifdef _G
 #undef _G
 #endif
