$NetBSD$

IRIX: <poll.h> has no INFTIM, childpid is a pid_t (long), TIOCNOTTY is in <sys/termios.h>.

--- client/runprog.c.orig
+++ client/runprog.c
@@ -16,7 +16,7 @@
  */
 
 
-int childpid = 0;	/* current child process's pid */
+pid_t childpid = 0;	/* current child process's pid */
 int tochild;		/* fd to write to child */
 int fromchild;		/* fd to read from child */
 int killedchild;	/* flag set on intr - flush output */ 
