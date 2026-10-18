$NetBSD$

No TIOCSCTTY (SVR4: IRIX): opening the tty after setsid() makes it the controlling one.

--- kitty/child.c.orig
+++ kitty/child.c
@@ -117,7 +117,9 @@
             int tfd = safe_open(name, O_RDWR | O_CLOEXEC, 0);
             if (tfd == -1) exit_on_err("Failed to open controlling terminal");
             // On BSD open() does not establish the controlling terminal
+#ifdef TIOCSCTTY  // SVR4 (IRIX): the open() above did it
             if (ioctl(tfd, TIOCSCTTY, 0) == -1) exit_on_err("Failed to set controlling terminal with TIOCSCTTY");
+#endif
             safe_close(tfd, __FILE__, __LINE__);
 
             fd_set passed_fds; FD_ZERO(&passed_fds); bool has_preserved_fds = false;
