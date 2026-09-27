$NetBSD$

IRIX 6.5.7's vsnprintf returns the count written, not needed: grow and
retry, which is right under both conventions; rewrite %zu.

--- compat/asprintf.c.orig
+++ compat/asprintf.c
@@ -37,28 +37,68 @@
 	return (n);
 }
 
+/*
+ * IRIX 6.5.7's vsnprintf predates C99: it has the old SUSv2 semantics and
+ * returns the number of characters ACTUALLY WRITTEN, never the number that
+ * would have been needed. Measured on 6.5.7:
+ *
+ *     vsnprintf(NULL, 0, "hello world", ...) == 0     (C99 says 11)
+ *     vsnprintf(buf,  4, "hello world", ...) == 3     (C99 says 11)
+ *
+ * The upstream implementation sizes the buffer with vsnprintf(NULL, 0, ...),
+ * so on IRIX it allocated one byte and every xasprintf() in tmux returned an
+ * empty string -- which is why tmux failed to start with a blank error
+ * message. (libevent carries an IRIX special case for exactly this, calling
+ * _xpg5_vsnprintf; that symbol does not exist in 6.5.7's libc.)
+ *
+ * Grow-and-retry instead. It is correct under BOTH conventions: under C99 the
+ * first oversized return tells us the exact size, and under SUSv2 we detect a
+ * full buffer and double.
+ */
 int
 vasprintf(char **ret, const char *fmt, va_list ap)
 {
+	size_t	 size = 128;
+	char	*buf;
 	int	 n;
-	va_list  ap2;
+	va_list	 ap2;
+#ifdef __sgi
+	char	 fmtbuf[1024];
 
-	va_copy(ap2, ap);
+	fmt = irix_fixfmt(fmt, fmtbuf, sizeof fmtbuf);
+#endif
 
-	if ((n = vsnprintf(NULL, 0, fmt, ap)) < 0)
-		goto error;
+	for (;;) {
+		buf = malloc(size);
+		if (buf == NULL)
+			goto error;
 
-	*ret = xmalloc(n + 1);
-	if ((n = vsnprintf(*ret, n + 1, fmt, ap2)) < 0) {
-		free(*ret);
-		goto error;
-	}
-	va_end(ap2);
+		va_copy(ap2, ap);
+		n = vsnprintf(buf, size, fmt, ap2);
+		va_end(ap2);
 
-	return (n);
+		/* Fits, with room for the NUL: done. Under SUSv2 a return of
+		 * exactly size - 1 is ambiguous (it may have been truncated),
+		 * so treat that as "too small" and grow. */
+		if (n >= 0 && (size_t)n < size - 1) {
+			*ret = buf;
+			return (n);
+		}
 
+		free(buf);
+
+		if (n > 0 && (size_t)n >= size - 1)
+			size = (size_t)n + 2;	/* C99 told us the length */
+		else
+			size *= 2;		/* SUSv2: just try bigger */
+
+		if (size > (16 * 1024 * 1024))
+			goto error;
+	}
+
 error:
-	va_end(ap2);
+	/* ap2 is already va_end'd at the bottom of each loop iteration; ending
+	 * it again here would be undefined. */
 	*ret = NULL;
 	return (-1);
 }
