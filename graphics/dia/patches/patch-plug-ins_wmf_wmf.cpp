$NetBSD$

Link gdi32 only with MSVC: clang honours the pragma on ELF too (lld then looks for libgdi32).

--- plug-ins/wmf/wmf.cpp.orig
+++ plug-ins/wmf/wmf.cpp
@@ -62,7 +62,9 @@
 #endif
 
 /* force linking with gdi32 */
+#ifdef _MSC_VER
 #pragma comment( lib, "gdi32" )
+#endif
 
 
 // #define SAVE_EMF
