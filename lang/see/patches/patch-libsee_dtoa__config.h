$NetBSD$

Handle MIPS, in either byte order.

--- libsee/dtoa_config.h.orig
+++ libsee/dtoa_config.h
@@ -12,11 +12,11 @@
 
 #include <see/type.h>
 
-#if defined(__i386__) || defined(__amd64__) || defined(__ia64__) || defined(__alpha__)
+#if defined(__i386__) || defined(__amd64__) || defined(__ia64__) || defined(__alpha__) || defined(__MIPSEL__)
 #   define IEEE_8087
 #endif
 
-#if defined(__m68k__) || defined(__sparc) || defined(__ppc__) || defined(__powerpc__)
+#if defined(__m68k__) || defined(__sparc) || defined(__ppc__) || defined(__powerpc__) || defined(__MIPSEB__)
 #   define IEEE_MC68k 
 #endif
 
