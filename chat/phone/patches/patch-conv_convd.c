$NetBSD: patch-conv_convd.c,v 1.3 2017/02/07 23:55:05 joerg Exp $

- Don't rely on __unused from netbsd's <cdefs.h> existing.
- Remove unused variable that causes build failure with gcc48.
- Add explicit casts if the constants are not value preserved
  on signed char platforms.
IRIX: <poll.h> has no INFTIM, childpid is a pid_t (long), TIOCNOTTY is in <sys/termios.h>.

--- conv/convd.c.orig
+++ conv/convd.c
@@ -38,6 +38,9 @@
 #include <stdlib.h>
 #include <err.h>
 #include <poll.h>
+#ifndef INFTIM
+#define INFTIM (-1)
+#endif
 #include <stdarg.h>
 #include <string.h>
 #include <fcntl.h>
@@ -48,6 +51,10 @@
 
 #include "../common.h"
 
+#ifndef __unused
+#define __unused __attribute__((__unused__))
+#endif
+
 #ifndef lint
 #if 0
 static char __unused char RCSid[] = "Header: convd.c,v 1.1 85/10/29 14:20:06 broome Exp ";
@@ -98,7 +105,6 @@
     int	 sl;
     int	 fds;
     int	 r;
-    int	 changed;
     static	int  new, old;
     struct	iovec iov[2];
     char	recvbuf[BUFSIZ];
@@ -113,7 +119,6 @@
     stayaround = 1;
     currslot = -1;
     highslot = -1;
-    changed = 0;
 
     signal(SIGPIPE, SIG_IGN);  /* we'll find out soon enough */
     signal(SIGALRM, sigalrm);  /* to handle timeout */
@@ -357,7 +362,7 @@
     char     sc;		/* used for slot number selection */
 
     /* tell user not to update screen until done with intro */
-    sc = META | UPDATE | 00;	
+    sc = (char)(META | UPDATE | 00);
     write(fd, &sc, 1);
 
     /* first go through and add all the windows */
@@ -404,7 +409,7 @@
     }
 
     /* now he can update the screen */
-    sc = META | UPDATE | 01;
+    sc = (char)(META | UPDATE | 01);
     write(fd, &sc, 1);
 }
 
