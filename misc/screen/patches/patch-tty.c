$NetBSD$

Without TIOCSCTTY (IRIX), get the controlling terminal by opening it after setsid(), as on SVR4.

--- tty.c.orig
+++ tty.c
@@ -614,12 +614,29 @@
  *  the bsdish variant.
  */
 
+/*
+ * Make fd's terminal the controlling one. Without TIOCSCTTY (IRIX), a
+ * session leader gets it, as on SVR4, by opening the terminal.
+ */
+static void settty_ctty(int fd)
+{
+#ifdef TIOCSCTTY
+	ioctl(fd, TIOCSCTTY, NULL);
+#else
+	char *name = ttyname(fd);
+	int t;
+
+	if (name && (t = open(name, O_RDWR)) >= 0)
+		close(t);
+#endif
+}
+
 void brktty(int fd)
 {
 	if (separate_sids)
 		setsid();	/* will break terminal affiliation */
 
-	ioctl(fd, TIOCSCTTY, NULL);
+	settty_ctty(fd);
 }
 
 int fgtty(int fd)
@@ -628,7 +645,7 @@
 
 	mypid = getpid();
 
-	ioctl(fd, TIOCSCTTY, NULL);
+	settty_ctty(fd);
 
 	if (separate_sids)
 		if (tcsetpgrp(fd, mypid))
