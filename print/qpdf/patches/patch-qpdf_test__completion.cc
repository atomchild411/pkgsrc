$NetBSD$

TIOCSCTTY only where there is one (not IRIX, where the test then runs without
making the pty its controlling terminal).

--- qpdf/test_completion.cc.orig
+++ qpdf/test_completion.cc
@@ -331,7 +331,9 @@
 
     // child process
     setsid();
+#ifdef TIOCSCTTY
     ioctl(secondary, TIOCSCTTY, 0);
+#endif
 
     close(primary);
     dup2(secondary, STDIN_FILENO);
