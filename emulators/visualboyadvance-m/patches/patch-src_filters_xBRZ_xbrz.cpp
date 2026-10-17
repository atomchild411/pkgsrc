$NetBSD$

The x87 fsqrt only on x86 (the #ifdef took any GNU compiler, and the rest of its line was ignored).

--- src/filters/xBRZ/xbrz.cpp.orig
+++ src/filters/xBRZ/xbrz.cpp
@@ -66,7 +66,7 @@
 
 inline double fastSqrt(double n)
 {
-#ifdef __GNUC__ || __clang__ || __MINGW64_VERSION_MAJOR || __MINGW32_MAJOR_VERSION
+#if (defined(__GNUC__) || defined(__clang__)) && (defined(__i386__) || defined(__x86_64__))
     __asm__ ("fsqrt" : "+t" (n));
     return n;
 #elif _MSC_VER && _M_IX86
