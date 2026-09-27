$NetBSD: patch-tmux.c,v 1.2 2025/10/05 11:04:21 leot Exp $

Add support for QNX.

IRIX 6.5 ships no UTF-8 locale; with utf8proc tmux does not need one.

--- tmux.c.orig
+++ tmux.c
@@ -22,7 +22,9 @@
 
 #include <errno.h>
 #include <fcntl.h>
-#include <langinfo.h>
+#ifndef __QNX__
+# include <langinfo.h>
+#endif
 #include <locale.h>
 #include <pwd.h>
 #include <signal.h>
@@ -361,9 +363,14 @@
 	    setlocale(LC_CTYPE, "C.UTF-8") == NULL) {
 		if (setlocale(LC_CTYPE, "") == NULL)
 			errx(1, "invalid LC_ALL, LC_CTYPE or LANG");
+/* IRIX 6.5 ships no UTF-8 locale at all (C, POSIX and ISO8859 only), so
+ * this check could never pass there; with utf8proc, widths and UTF-8
+ * decoding do not come from the C library's locale anyway. */
+#if !defined(__QNX__) && !(defined(__sgi) && defined(HAVE_UTF8PROC))
 		s = nl_langinfo(CODESET);
 		if (strcasecmp(s, "UTF-8") != 0 && strcasecmp(s, "UTF8") != 0)
 			errx(1, "need UTF-8 locale (LC_CTYPE) but have %s", s);
+#endif
 	}
 
 	setlocale(LC_TIME, "");
