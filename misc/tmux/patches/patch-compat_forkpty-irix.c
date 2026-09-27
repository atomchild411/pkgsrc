$NetBSD$

New: forkpty for IRIX (/dev/ptmx).

--- compat/forkpty-irix.c.orig
+++ compat/forkpty-irix.c
@@ -0,0 +1,104 @@
+/* forkpty() for IRIX 6.5.
+ *
+ * IRIX has no forkpty()/openpty() and no <pty.h>, but it does have the full
+ * SVR4 STREAMS pty machinery: /dev/ptmx plus grantpt/unlockpt/ptsname, and a
+ * /dev/pts directory. So this is tmux's Solaris implementation with two
+ * IRIX-specific differences noted below.
+ *
+ * Derived from compat/forkpty-sunos.c (ISC licence, as below).
+ *
+ * Copyright (c) 2009 Todd Carson <toc@daybefore.net>
+ *
+ * Permission to use, copy, modify, and distribute this software for any
+ * purpose with or without fee is hereby granted, provided that the above
+ * copyright notice and this permission notice appear in all copies.
+ *
+ * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
+ * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
+ * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
+ * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
+ * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
+ * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
+ * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
+ */
+
+#include <sys/types.h>
+#include <sys/ioctl.h>
+
+#include <fcntl.h>
+#include <stdlib.h>
+#include <string.h>
+#include <strings.h>
+#include <stropts.h>
+#include <termios.h>
+#include <unistd.h>
+
+#include "compat.h"
+
+void fatal(const char *, ...);
+void fatalx(const char *, ...);
+
+pid_t
+forkpty(int *master, char *name, struct termios *tio, struct winsize *ws)
+{
+	int	slave = -1;
+	char   *path;
+	pid_t	pid;
+
+	if ((*master = open("/dev/ptmx", O_RDWR|O_NOCTTY)) == -1)
+		return (-1);
+	if (grantpt(*master) != 0)
+		goto out;
+	if (unlockpt(*master) != 0)
+		goto out;
+
+	if ((path = ptsname(*master)) == NULL)
+		goto out;
+	if (name != NULL)
+		strlcpy(name, path, TTY_NAME_MAX);
+	if ((slave = open(path, O_RDWR|O_NOCTTY)) == -1)
+		goto out;
+
+	switch (pid = fork()) {
+	case -1:
+		goto out;
+	case 0:
+		close(*master);
+
+		setsid();
+#ifdef TIOCSCTTY
+		if (ioctl(slave, TIOCSCTTY, NULL) == -1)
+			fatal("ioctl failed");
+#endif
+
+		/* DIFFERENCE 1 from the Solaris version: IRIX pushes ptem and
+		 * ldterm onto the slave itself when it is opened, so pushing
+		 * them again returns EINVAL. Solaris requires the explicit
+		 * push and treats failure as fatal; here failure is the normal
+		 * case, so try and ignore the result rather than dying. */
+		(void)ioctl(slave, I_PUSH, "ptem");
+		(void)ioctl(slave, I_PUSH, "ldterm");
+
+		if (tio != NULL && tcsetattr(slave, TCSAFLUSH, tio) == -1)
+			fatal("tcsetattr failed");
+		if (ioctl(slave, TIOCSWINSZ, ws) == -1)
+			fatal("ioctl failed");
+
+		dup2(slave, 0);
+		dup2(slave, 1);
+		dup2(slave, 2);
+		if (slave > 2)
+			close(slave);
+		return (0);
+	}
+
+	close(slave);
+	return (pid);
+
+out:
+	if (*master != -1)
+		close(*master);
+	if (slave != -1)
+		close(slave);
+	return (-1);
+}
