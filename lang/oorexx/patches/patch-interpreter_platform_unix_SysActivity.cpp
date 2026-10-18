$NetBSD$

IRIX has no call that returns a thread's stack: estimate it.

--- interpreter/platform/unix/SysActivity.cpp.orig
+++ interpreter/platform/unix/SysActivity.cpp
@@ -177,6 +177,11 @@
     // stack address points to the start of the stack (the high address),
     // not the base, how it's returned by pthread_get_stackaddr_np
     return (char *)pthread_get_stackaddr_np(thread) - size;
+#elif defined(__sgi)
+    // IRIX cannot tell a thread its stack: assume a stack of getStackSize()
+    // whose high end is a little above this frame.
+    char here;
+    return &here - getStackSize() + 64 * 1024;
 #else
 #error no code for getStackBase()
 #endif
@@ -217,6 +222,10 @@
 #elif defined HAVE_PTHREAD_GET_STACKSIZE_NP
     // MacOS
     return pthread_get_stacksize_np(pthread_self());
+#elif defined(__sgi)
+    // what create() then asks for; the main thread's stack (RLIMIT_STACK)
+    // is larger
+    return 8 * 1024 * 1024;
 #else
 #error no code for getStackSize()
 #endif
