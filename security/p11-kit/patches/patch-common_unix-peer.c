$NetBSD$

IRIX has no way to learn a unix socket peer's credentials (no
SO_PEERCRED, getpeereid or getpeerucred): fail, so the server refuses
the client rather than trusting it.

--- common/unix-peer.c.orig
+++ common/unix-peer.c
@@ -106,6 +106,11 @@
 
 	if (ret)
 		return -1;
+#elif defined(__sgi)
+	/* IRIX cannot tell who is at the other end of a unix socket. */
+	(void)ret;
+	errno = ENOTSUP;
+	return -1;
 #else
 #error "Unsupported UNIX variant"
 #endif
