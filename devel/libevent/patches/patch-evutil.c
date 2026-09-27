$NetBSD$

IRIX 6.5.7: no _xpg5_vsnprintf (keep that branch for later IRIX only), and
no if_nametoindex() (6.5's IPv6 predates RFC 2553).  From the hand-built
libevent proven on IRIX (tools/irix-cross/pkg/patches).

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
@@ -1988,6 +1995,20 @@
 #endif
 }
 
+/* IRIX 6.5's IPv6 predates RFC 2553: there is no if_nametoindex(), and no
+ * interface-index API at all. 0 is the documented "unknown interface" return,
+ * which makes the caller fall through to parsing the zone as a number -- the
+ * only form this system could act on anyway. libevent's configure does not
+ * probe for this function; it simply assumes it exists. */
+#ifdef __sgi
+static unsigned int
+if_nametoindex(const char *name)
+{
+	(void)name;
+	return 0;
+}
+#endif
+
 int
 evutil_inet_pton_scope(int af, const char *src, void *dst, unsigned *indexp)
 {
