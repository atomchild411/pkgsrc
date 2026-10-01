$NetBSD$

IRIX has the SVR4 pty interfaces (/dev/ptmx, grantpt, STREAMS) but no <pty.h>; its <sys/stream.h> clashes with nvim's struct queue, so it gets its own include branch. No TIOCSCTTY: the session leader acquires the terminal by opening it. The STREAMS modules are pushed in the child's new session: pushing them in a server that leads a session with no terminal (nvim under its TUI) makes the pty that server's controlling terminal. Save and restore SIGCHLD around grantpt() with sigaction: System V signal() loses libuv's handler mask and SA_RESTART, which deadlocks libuv's signal lock.

--- src/nvim/os/pty_proc_unix.c.orig
+++ src/nvim/os/pty_proc_unix.c
@@ -18,6 +18,10 @@
 int forkpty(int *, char *, const struct termios *, const struct winsize *);
 #elif defined(__OpenBSD__) || defined(__NetBSD__) || defined(__APPLE__)
 # include <util.h>
+#elif defined(__sgi)
+// IRIX: the SVR4 fallback below; I_PUSH comes from <sys/stropts.h>.
+# include <fcntl.h>
+# include <unistd.h>
 #elif defined(__sun)
 # include <fcntl.h>
 # include <signal.h>
@@ -62,6 +66,24 @@ int forkpty(int *, char *, const struct termios *, const struct winsize *);
 #  define I_PUSH 0  // XXX: find the actual value
 # endif
 
+static void vim_setup_slave(int slave, struct termios *termp, struct winsize *winp)
+{
+  // ptem emulates a terminal when used on a pseudo terminal driver,
+  // must be pushed before ldterm
+  ioctl(slave, I_PUSH, "ptem");
+  // ldterm provides most of the termio terminal interface
+  ioctl(slave, I_PUSH, "ldterm");
+  // ttcompat compatibility with older terminal ioctls
+  ioctl(slave, I_PUSH, "ttcompat");
+
+  if (termp) {
+    tcsetattr(slave, TCSAFLUSH, termp);
+  }
+  if (winp) {
+    ioctl(slave, TIOCSWINSZ, winp);
+  }
+}
+
 static int vim_openpty(int *amaster, int *aslave, char *name, struct termios *termp,
                        struct winsize *winp)
 {
@@ -74,9 +96,17 @@ static int vim_openpty(int *amaster, int *aslave, char *name, struct termios *te
   // grantpt will invoke a setuid program to change permissions
   // and might fail if SIGCHLD handler is set, temporarily reset
   // while running
-  void (*sig_saved)(int) = signal(SIGCHLD, SIG_DFL);
+  // (With sigaction, not signal(): on System V systems such as IRIX,
+  // signal() would put libuv's handler back without its signal mask and
+  // SA_RESTART, and libuv's signal lock then deadlocks when a second
+  // signal arrives inside the handler.)
+  struct sigaction sa_dfl, sa_saved;
+  memset(&sa_dfl, 0, sizeof(sa_dfl));
+  sa_dfl.sa_handler = SIG_DFL;
+  sigemptyset(&sa_dfl.sa_mask);
+  sigaction(SIGCHLD, &sa_dfl, &sa_saved);
   int res = grantpt(master);
-  signal(SIGCHLD, sig_saved);
+  sigaction(SIGCHLD, &sa_saved, NULL);
 
   if (res == -1 || unlockpt(master) == -1) {
     goto error;
@@ -92,20 +122,9 @@ static int vim_openpty(int *amaster, int *aslave, char *name, struct termios *te
     goto error;
   }
 
-  // ptem emulates a terminal when used on a pseudo terminal driver,
-  // must be pushed before ldterm
-  ioctl(slave, I_PUSH, "ptem");
-  // ldterm provides most of the termio terminal interface
-  ioctl(slave, I_PUSH, "ldterm");
-  // ttcompat compatibility with older terminal ioctls
-  ioctl(slave, I_PUSH, "ttcompat");
-
-  if (termp) {
-    tcsetattr(slave, TCSAFLUSH, termp);
-  }
-  if (winp) {
-    ioctl(slave, TIOCSWINSZ, winp);
-  }
+#ifndef __sgi
+  vim_setup_slave(slave, termp, winp);
+#endif
 
   *amaster = master;
   *aslave = slave;
@@ -126,9 +145,22 @@ error:
 static int vim_login_tty(int fd)
 {
   setsid();
+#ifdef TIOCSCTTY
   if (ioctl(fd, TIOCSCTTY, NULL) == -1) {
     return -1;
   }
+#else
+  // SVR4 (IRIX): a session leader's first open of a terminal, without
+  // O_NOCTTY, makes it the controlling terminal.
+  {
+    char *name = ttyname(fd);
+    int ctty;
+    if (name == NULL || (ctty = open(name, O_RDWR)) == -1) {
+      return -1;
+    }
+    close(ctty);
+  }
+#endif
 
   dup2(fd, STDIN_FILENO);
   dup2(fd, STDOUT_FILENO);
@@ -155,6 +187,14 @@ pid_t vim_forkpty(int *amaster, char *name, struct termios *termp, struct winsiz
     return -1;
   case 0:
     close(master);
+#ifdef __sgi
+    // IRIX: pushing ptem and ldterm makes the stream the controlling
+    // terminal of a session leader that has none, O_NOCTTY notwithstanding,
+    // and under the TUI the nvim server is such a session leader: it would
+    // take the terminal from the job. Push in the new session instead.
+    setsid();
+    vim_setup_slave(slave, termp, winp);
+#endif
     vim_login_tty(slave);
     return 0;
   default:
