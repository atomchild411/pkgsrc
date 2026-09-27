$NetBSD$

New: IRIX osdep file (round, strsignal, irix_fixfmt, osdep_*).

--- osdep-irix.c.orig
+++ osdep-irix.c
@@ -0,0 +1,130 @@
+/* $OpenBSD$ */
+
+/*
+ * Copyright (c) 2009 Nicholas Marriott <nicholas.marriott@gmail.com>
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
+
+#include <math.h>
+#include <string.h>
+#include <signal.h>
+#include <stdio.h>
+
+#include "tmux.h"
+
+/* IRIX 6.5's libm predates C99: it has rint(), floor() and trunc() but no
+ * round(). Implemented via trunc rather than the usual floor(x + 0.5) because
+ * that idiom is wrong for the largest double below 0.5 (0.49999999999999994 +
+ * 0.5 rounds up to 1.0, so floor gives 1 where round must give 0). Here d is
+ * the fractional part carrying x's sign and |d| < 1, so stepping away from
+ * zero when |d| >= 0.5 is exactly C99's "round half away from zero". For
+ * |x| >= 2^52 the value is already integral, trunc(x) == x, d == 0. */
+double
+round(double x)
+{
+	double	t = trunc(x);
+	double	d = x - t;
+
+	if (d >= 0.5)
+		t += 1.0;
+	else if (d <= -0.5)
+		t -= 1.0;
+	return (t);
+}
+
+/* IRIX 6.5 has no strsignal(). It does export sys_siglist/NSIG, which is what
+ * strsignal is specified to return, so this is a faithful implementation
+ * rather than a stub. Declared in compat.h under __sgi. */
+char *
+strsignal(int signo)
+{
+	static char	buf[32];
+
+	/* IRIX's <signal.h> declares the underscore-prefixed name; libc exports
+	 * both sys_siglist (weak) and _sys_siglist at the same address, but only
+	 * _sys_siglist has a declaration, so use that one. NSIG is 65 here and
+	 * the array has exactly that many entries. */
+	if (signo > 0 && signo < NSIG && _sys_siglist[signo] != NULL)
+		return ((char *)_sys_siglist[signo]);
+	xsnprintf(buf, sizeof buf, "Unknown signal %d", signo);
+	return (buf);
+}
+
+char *
+osdep_get_name(__unused int fd, __unused char *tty)
+{
+	return (NULL);
+}
+
+char *
+osdep_get_cwd(int fd)
+{
+	return (NULL);
+}
+
+struct event_base *
+osdep_event_init(void)
+{
+	return (event_init());
+}
+
+/*
+ * IRIX 6.5.7's printf family predates C99 and does not understand the 'z'
+ * length modifier: "%zu" comes out literally as "zu", and the argument is not
+ * consumed -- so everything after it in the same format string is shifted.
+ * tmux uses %zu in 52 places, which is why pane listings showed
+ * "[history 0/2000, zu bytes]".
+ *
+ * Rewrite 'z' to 'l' on the way through. That is exact here, not a guess: on
+ * n32 size_t and unsigned long are both 32 bits and occupy the same vararg
+ * slot. Called from vasprintf() and xvsnprintf(), which between them are the
+ * funnel for every formatted string tmux produces.
+ */
+const char *
+irix_fixfmt(const char *fmt, char *buf, size_t buflen)
+{
+	const char	*f;
+	size_t		 o = 0;
+	int		 inspec = 0;
+
+	if (strchr(fmt, 'z') == NULL)
+		return (fmt);
+
+	for (f = fmt; *f != '\0'; f++) {
+		if (o + 2 >= buflen)
+			return (fmt);	/* too long to rewrite; use as-is */
+		if (!inspec) {
+			buf[o++] = *f;
+			if (*f == '%')
+				inspec = 1;
+			continue;
+		}
+		if (*f == '%') {		/* %% */
+			buf[o++] = *f;
+			inspec = 0;
+			continue;
+		}
+		if (*f == 'z') {
+			buf[o++] = 'l';
+			continue;
+		}
+		buf[o++] = *f;
+		if (strchr("diouxXeEfgGaAcspn", *f) != NULL)
+			inspec = 0;
+	}
+	buf[o] = '\0';
+	return (buf);
+}
