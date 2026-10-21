$NetBSD: patch-include_violite.h,v 1.1 2022/11/27 22:12:25 nia Exp $

pthread_t on NetBSD is a pointer to a struct. To account for the
C++ type system we need to use an actual NULL pointer rather than
an incompatible integer type.
Build comp_err also in a cross build that has an emulator to run it
(CMAKE_CROSSCOMPILING_EMULATOR, the IRIX irix-exec bridge).
IRIX has neither ppoll nor kqueue: poll() in vio, as on Windows.
The bundled boost's MIPSpro workaround is not for clang, which defines
_COMPILER_VERSION on IRIX too.

--- include/violite.h.orig
+++ include/violite.h
@@ -52,7 +52,7 @@
 
 /* Simple vio interface in C;  The functions are implemented in violite.c */
 
-#if !defined(_WIN32) && !defined(HAVE_KQUEUE)
+#if !defined(_WIN32) && !defined(HAVE_KQUEUE) && !defined(__sgi)
 #define USE_PPOLL_IN_VIO
 #endif
 
@@ -344,7 +344,11 @@
     It is initialized to 0 here, meaning don't attempt to send a signal, to
     keep non-server code unaffected.
   */
+#ifdef __NetBSD__
+  std::optional<my_thread_t> thread_id = nullptr;
+#else
   std::optional<my_thread_t> thread_id = 0;
+#endif
   sigset_t signal_mask;  // Signal mask
   /*
     Flag to indicate whether we are in poll or shutdown.
