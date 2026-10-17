$NetBSD$

IRIX: openpty and login_tty come from <pty.h> (compiler-rt); IRIX has no TIOCSCTTY, so the child takes its terminal with login_tty.

--- st.c.orig
+++ st.c
@@ -26,6 +26,8 @@
  #include <util.h>
 #elif defined(__FreeBSD__) || defined(__DragonFly__)
  #include <libutil.h>
+#elif defined(__sgi)
+ #include <pty.h>
 #endif
 
 /* Arbitrary sizes */
@@ -802,6 +804,11 @@
 	case 0:
 		close(iofd);
 		close(m);
+#ifdef __sgi
+		/* no TIOCSCTTY: login_tty takes the terminal by opening it */
+		if (login_tty(s) < 0)
+			die("login_tty failed: %s\n", strerror(errno));
+#else
 		setsid(); /* create a new process group */
 		dup2(s, 0);
 		dup2(s, 1);
@@ -810,6 +817,7 @@
 			die("ioctl TIOCSCTTY failed: %s\n", strerror(errno));
 		if (s > 2)
 			close(s);
+#endif
 #ifdef __OpenBSD__
 		if (pledge("stdio getpw proc exec", NULL) == -1)
 			die("pledge\n");
