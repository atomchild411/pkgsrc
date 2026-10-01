$NetBSD$

Apply MacPorts patch-libuv-unix-core-close-nocancel.diff for
- older gcc versions to not error on pragmas
- 32bit code to link correctly
- Tiger to work around not having a non-cancellable close function

IRIX: the online processor count is _SC_NPROC_ONLN.

--- src/unix/core.c.orig
+++ src/unix/core.c
@@ -597,18 +597,31 @@ int uv__accept(int sockfd) {
  * will unwind the thread when it's in the cancel state. Work around that
  * by making the system call directly. Musl libc is unaffected.
  */
+
+#if defined(__GNUC__)
+# define GCC_VERSION \
+	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
+#endif
+#if defined(__clang__) || (defined(GCC_VERSION) && (GCC_VERSION >= 40500))
+/* gcc diagnostic pragmas available */
+# define GCC_DIAGNOSTIC_AVAILABLE
+#endif
 int uv__close_nocancel(int fd) {
-#if defined(__APPLE__)
-#pragma GCC diagnostic push
-#pragma GCC diagnostic ignored "-Wdollar-in-identifier-extension"
-#if defined(__LP64__) || TARGET_OS_IPHONE
+#if defined(__APPLE__) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1050)
+# if defined(GCC_DIAGNOSTIC_AVAILABLE)
+#  pragma GCC diagnostic push
+#  pragma GCC diagnostic ignored "-Wdollar-in-identifier-extension"
+# endif
+# if defined(__LP64__) || __LP64__ || (defined(TARGET_OS_IPHONE) && (TARGET_OS_IPHONE > 0))
   extern int close$NOCANCEL(int);
   return close$NOCANCEL(fd);
-#else
+# else
   extern int close$NOCANCEL$UNIX2003(int);
   return close$NOCANCEL$UNIX2003(fd);
-#endif
-#pragma GCC diagnostic pop
+# endif
+# if defined(GCC_DIAGNOSTIC_AVAILABLE)
+#  pragma GCC diagnostic pop
+# endif
 #elif defined(__linux__) && defined(__SANITIZE_THREAD__) && defined(__clang__)
   long rc;
   __sanitizer_syscall_pre_close(fd);
@@ -2121,8 +2134,13 @@ unsigned int uv_available_parallelism(void) {
   }
 #endif /* __linux__ */
 
+#if defined(__sgi)
+  if (rc < 0)
+    rc = sysconf(_SC_NPROC_ONLN);
+#else
   if (rc < 0)
     rc = sysconf(_SC_NPROCESSORS_ONLN);
+#endif
 
 #ifdef __linux__
   {
