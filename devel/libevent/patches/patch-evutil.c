$NetBSD$

IRIX 6.5.7: no _xpg5_vsnprintf (keep that branch for later IRIX only).
From the hand-built libevent proven on IRIX (tools/irix-cross/pkg/patches).
(if_nametoindex comes from the toolchain now: compiler-rt irix/netdb.c.)

--- evutil.c.orig
+++ evutil.c
@@ -1875,8 +1875,15 @@
 	r = _vsnprintf(buf, buflen, format, ap);
 	if (r < 0)
 		r = _vscprintf(format, ap);
-#elif defined(sgi)
-	/* Make sure we always use the correct vsnprintf on IRIX */
+#elif defined(sgi) && defined(EVENT__HAVE_XPG5_VSNPRINTF)
+	/* Make sure we always use the correct vsnprintf on IRIX.
+	 *
+	 * Disabled on IRIX 6.5.7: _xpg5_vsnprintf is not in its libc (nor is
+	 * _xpg5_snprintf), and __SGI_LIBC_NAMESPACE_QUALIFIER is defined nowhere
+	 * in its headers -- both belong to a later IRIX. 6.5.7 exports a plain
+	 * conforming vsnprintf, so the generic branch below is correct here.
+	 * Guarded on a macro nothing defines rather than deleted, so the intent
+	 * survives for anyone on a newer IRIX. */
 	extern int      _xpg5_vsnprintf(char * __restrict,
 		__SGI_LIBC_NAMESPACE_QUALIFIER size_t,
 		const char * __restrict, /* va_list */ char *);
