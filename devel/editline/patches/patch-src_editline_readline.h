$NetBSD$

IRIX has no <sys/ttydefaults.h> (CTRL() comes from <sys/termios.h>).

--- src/editline/readline.h.orig
+++ src/editline/readline.h
@@ -78,7 +78,7 @@
 
 #ifndef CTRL
 #include <sys/ioctl.h>
-#if !defined(__sun) && !defined(__hpux) && !defined(_AIX)
+#if !defined(__sun) && !defined(__hpux) && !defined(_AIX) && !defined(__sgi)
 #include <sys/ttydefaults.h>
 #endif
 #ifndef CTRL
