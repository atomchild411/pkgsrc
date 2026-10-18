$NetBSD$

IRIX: clang's <unwind.h> declares _Unwind_GetIPInfo, returning n32's 64-bit _Unwind_Word.

--- contrib/backward-cpp/backward.hpp.orig
+++ contrib/backward-cpp/backward.hpp
@@ -398,7 +398,7 @@
 // anyway.
 //
 // Luckily we can play on the fact that the guard macros have a different name:
-#ifdef __CLANG_UNWIND_H
+#if defined(__CLANG_UNWIND_H) && !defined(__sgi)
 // In fact, this function still comes from libgcc (on my different linux boxes,
 // clang links against libgcc).
 #include <inttypes.h>
