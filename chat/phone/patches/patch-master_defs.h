$NetBSD: patch-master_defs.h,v 1.1 2014/09/11 07:15:56 dholland Exp $

- Don't rely on __unused from netbsd's <cdefs.h> existing.
IRIX: <poll.h> has no INFTIM, childpid is a pid_t (long), TIOCNOTTY is in <sys/termios.h>.

--- master/defs.h.orig
+++ master/defs.h
@@ -14,7 +14,11 @@
 #include <sys/socket.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
+#ifdef __sgi
+#include <sys/termios.h>
+#else
 #include <sys/tty.h>
+#endif
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <stdio.h>
@@ -26,6 +30,9 @@
 #include <stdlib.h>
 #include <unistd.h>
 #include <poll.h>
+#ifndef INFTIM
+#define INFTIM (-1)
+#endif
 #include <pwd.h>
 #include <stdarg.h>
 #include <string.h>
@@ -33,6 +40,10 @@
 #include <err.h>
 #include <errno.h>
 
+#ifndef __unused
+#define __unused __attribute__((__unused__))
+#endif
+
 #define SOCKADDR    struct sockaddr_in	  /* shorter to type */
 
 /*
