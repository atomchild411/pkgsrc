$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/thread.cpp.orig
+++ src/thread.cpp
@@ -73,6 +73,11 @@ unsigned thread::hardware_concurrency() noexcept {
   if (result < 0)
     return 0;
   return static_cast<unsigned>(result);
+#elif defined(_SC_NPROC_ONLN) // IRIX
+  long result = sysconf(_SC_NPROC_ONLN);
+  if (result < 0)
+    return 0;
+  return static_cast<unsigned>(result);
 #elif defined(_LIBCPP_WIN32API)
   SYSTEM_INFO info;
   GetSystemInfo(&info);
