$NetBSD$

IRIX has no F_DUPFD_CLOEXEC: F_DUPFD, then FD_CLOEXEC.

--- src/nvim/channel.c.orig
+++ src/nvim/channel.c
@@ -591,8 +591,20 @@ uint64_t channel_from_stdio(bool rpc, CallbackReader on_output, const char **err
     // Redirect stdout/stdin (the UI channel) to stderr. Use fnctl(F_DUPFD_CLOEXEC) instead of dup()
     // to prevent child processes from inheriting the file descriptors, which are used by UIs to
     // detect when Nvim exits.
+#ifdef F_DUPFD_CLOEXEC
     stdin_dup_fd = fcntl(STDIN_FILENO, F_DUPFD_CLOEXEC, STDERR_FILENO + 1);
     stdout_dup_fd = fcntl(STDOUT_FILENO, F_DUPFD_CLOEXEC, STDERR_FILENO + 1);
+#else
+    // No F_DUPFD_CLOEXEC (IRIX): duplicate, then mark close-on-exec.
+    stdin_dup_fd = fcntl(STDIN_FILENO, F_DUPFD, STDERR_FILENO + 1);
+    stdout_dup_fd = fcntl(STDOUT_FILENO, F_DUPFD, STDERR_FILENO + 1);
+    if (stdin_dup_fd != -1) {
+      (void)fcntl(stdin_dup_fd, F_SETFD, FD_CLOEXEC);
+    }
+    if (stdout_dup_fd != -1) {
+      (void)fcntl(stdout_dup_fd, F_SETFD, FD_CLOEXEC);
+    }
+#endif
     dup2(STDERR_FILENO, STDOUT_FILENO);
     dup2(STDERR_FILENO, STDIN_FILENO);
   }
