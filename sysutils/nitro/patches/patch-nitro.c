$NetBSD$

IRIX: no TIOCSCTTY (reopen the terminal as session leader, SVR4) or _PATH_STDPATH.

--- nitro.c.orig
+++ nitro.c
@@ -40,6 +40,26 @@
 
 #include "nitro.h"
 
+#ifndef _PATH_STDPATH	/* IRIX */
+#define _PATH_STDPATH "/usr/sbin:/usr/bsd:/sbin:/usr/bin:/bin"
+#endif
+
+/* Make fd 0's terminal the controlling one; only works after setsid. */
+static void
+acquire_ctty(void)
+{
+#ifdef TIOCSCTTY
+	ioctl(0, TIOCSCTTY, 1);
+#else
+	/* SVR4 (IRIX): a session leader's next open of a tty does it. */
+	char *tn = ttyname(0);
+	int tfd;
+
+	if (tn != NULL && (tfd = open(tn, O_RDWR)) >= 0)
+		close(tfd);
+#endif
+}
+
 #define DELAY_SPAWN_ERROR 2000   /* ms to wait when fork failed */
 #define DELAY_STARTING 2000      /* ms until s service is considered up */
 #define DELAY_RESPAWN 1000       /* ms to wait if a serviced crashed when starting */
@@ -557,7 +577,7 @@
 		if (strcmp(services[i].name, "SYS") == 0) {
 			// keep fd connected to console, acquire controlling tty
 			// only works after setsid!
-			ioctl(0, TIOCSCTTY, 1);
+			acquire_ctty();
 		} else {
 			dup2(nullfd, 0);
 		}
@@ -1264,7 +1284,7 @@
 	dup2(ttyfd, 2);
 	if (ttyfd > 2)
 		close(ttyfd);
-	ioctl(0, TIOCSCTTY, 1);
+	acquire_ctty();
 }
 
 void
