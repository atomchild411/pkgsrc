$NetBSD$

No TIOCSCTTY (SVR4: IRIX): opening the tty after setsid() did it.

--- bin/varnishtest/vtc_process.c.orig
+++ bin/varnishtest/vtc_process.c
@@ -761,7 +761,7 @@
 		if (ioctl(slave, I_PUSH, "ldterm"))
 			vtc_log(p->vl, 4, "PUSH ldterm: %s", strerror(errno));
 		(void)ioctl(STDIN_FILENO, TIOCSCTTY, NULL);
-#else
+#elif defined(TIOCSCTTY)	/* else (SVR4: IRIX) the open() above did it */
 		AZ(ioctl(STDIN_FILENO, TIOCSCTTY, NULL));
 #endif
 		AZ(close(STDOUT_FILENO));
