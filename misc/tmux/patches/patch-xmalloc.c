$NetBSD$

IRIX's printf has no %zu: rewrite the format (irix_fixfmt, osdep-irix.c).

--- xmalloc.c.orig
+++ xmalloc.c
@@ -152,7 +152,16 @@
 	if (len > INT_MAX)
 		fatalx("xsnprintf: len > INT_MAX");
 
+#ifdef __sgi
+	{
+		char	fmtbuf[1024];
+
+		fmt = irix_fixfmt(fmt, fmtbuf, sizeof fmtbuf);
+		i = vsnprintf(str, len, fmt, ap);
+	}
+#else
 	i = vsnprintf(str, len, fmt, ap);
+#endif
 
 	if (i < 0 || i >= (int)len)
 		fatalx("xsnprintf: overflow");
