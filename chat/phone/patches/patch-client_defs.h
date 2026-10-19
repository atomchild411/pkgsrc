$NetBSD: patch-client_defs.h,v 1.2 2015/11/07 22:19:46 dholland Exp $

- Don't rely on __unused from netbsd's <cdefs.h> existing.
- Use a more portable username size symbol for the sake of Solaris.
- Also include limits.h to make sure that symbol is defined.
IRIX: <poll.h> has no INFTIM, childpid is a pid_t (long), TIOCNOTTY is in <sys/termios.h>.

--- client/defs.h.orig
+++ client/defs.h
@@ -22,8 +22,16 @@
 #include <stdarg.h>
 #include <errno.h>
 #include <poll.h>
+#ifndef INFTIM
+#define INFTIM (-1)
+#endif
 #include <curses.h>
 #include <netdb.h>
+#include <limits.h>
+
+#ifndef __unused
+#define __unused __attribute__((__unused__))
+#endif
 
 int	msgpending;
 int	killedchild;
@@ -38,7 +46,7 @@
 char	*home;			    /* home directory	       */
 const char *shell;		    /* preferred shell	       */
 char	myhost[MAXHOSTNAMELEN];	    /* local host name	       */
-char	realname[MAXLOGNAME];	    /* from password file      */
+char	realname[LOGIN_NAME_MAX];   /* from password file      */
 int	maxx;			    /* max legal x coordinate  */
 int	maxy;			    /* max legal y coordinate  */
 int	stream;			    /* stream socket filedes   */
