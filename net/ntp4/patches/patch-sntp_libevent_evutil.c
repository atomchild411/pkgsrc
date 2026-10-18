$NetBSD$

IRIX 6.5.7 has no _xpg5_vsnprintf (as devel/libevent).

--- sntp/libevent/evutil.c.orig
+++ sntp/libevent/evutil.c
@@ -1812,8 +1812,9 @@
 	r = _vsnprintf(buf, buflen, format, ap);
 	if (r < 0)
 		r = _vscprintf(format, ap);
-#elif defined(sgi)
-	/* Make sure we always use the correct vsnprintf on IRIX */
+#elif defined(sgi) && defined(EVENT__HAVE_XPG5_VSNPRINTF)
+	/* Make sure we always use the correct vsnprintf on IRIX (not 6.5.7,
+	 * whose libc lacks _xpg5_vsnprintf; as devel/libevent). */
 	extern int      _xpg5_vsnprintf(char * __restrict,
 		__SGI_LIBC_NAMESPACE_QUALIFIER size_t,
 		const char * __restrict, /* va_list */ char *);
