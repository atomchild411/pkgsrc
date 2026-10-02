$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/filesystem/operations.cpp.orig
+++ src/filesystem/operations.cpp
@@ -825,7 +825,7 @@ bool __remove(const path& p, error_code* ec) {
 //
 // The second implementation is used on platforms where `openat()` & friends are available,
 // and it threads file descriptors through recursive calls to avoid such race conditions.
-#if defined(_LIBCPP_WIN32API) || defined(__MVS__)
+#if defined(_LIBCPP_WIN32API) || defined(__MVS__) || defined(__sgi)
 #  define REMOVE_ALL_USE_DIRECTORY_ITERATOR
 #endif
 
