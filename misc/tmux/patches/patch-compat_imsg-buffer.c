$NetBSD: patch-compat_imsg-buffer.c,v 1.3 2026/01/18 20:30:49 wiz Exp $

Add support for QNX.

IRIX 6.5 (_SGIAPI) passes descriptors with the BSD 4.3 msg_accrights,
not SCM_RIGHTS/cmsghdr.

--- compat/imsg-buffer.c.orig
+++ compat/imsg-buffer.c
@@ -44,6 +44,10 @@
 #define be32toh ntohl
 #undef be64toh
 #define be64toh ntohll
+
+#if defined(__QNX__) && !defined(IOV_MAX)
+# define IOV_MAX 16
+#endif
 
 struct ibufqueue {
 	TAILQ_HEAD(, ibuf)	bufs;
@@ -756,6 +760,11 @@
 	return (0);
 }
 
+/* IRIX 6.5 under _SGIAPI has the original BSD msghdr: descriptors are passed
+ * as a bare array of ints in msg_accrights, with NO cmsghdr wrapper (the
+ * SCM_RIGHTS/CMSG_* protocol belongs to IRIX's XPG4 personality, which
+ * _XOPEN_SOURCE would switch on for the whole program).  Use the native
+ * interface in the two places that pass descriptors. */
 int
 msgbuf_write(int fd, struct msgbuf *msgbuf)
 {
@@ -764,15 +773,19 @@
 	unsigned int	 i = 0;
 	ssize_t		 n;
 	struct msghdr	 msg;
+#ifndef __sgi
 	struct cmsghdr	*cmsg;
 	union {
 		struct cmsghdr	hdr;
 		char		buf[CMSG_SPACE(sizeof(int))];
 	} cmsgbuf;
+#endif
 
 	memset(&iov, 0, sizeof(iov));
 	memset(&msg, 0, sizeof(msg));
+#ifndef __sgi
 	memset(&cmsgbuf, 0, sizeof(cmsgbuf));
+#endif
 	TAILQ_FOREACH(buf, &msgbuf->bufs.bufs, entry) {
 		if (i >= IOV_MAX)
 			break;
@@ -792,6 +805,10 @@
 	msg.msg_iovlen = i;
 
 	if (buf0 != NULL) {
+#ifdef __sgi
+		msg.msg_accrights = (caddr_t)&buf0->fd;
+		msg.msg_accrightslen = sizeof(int);
+#else
 		msg.msg_control = (caddr_t)&cmsgbuf.buf;
 		msg.msg_controllen = sizeof(cmsgbuf.buf);
 		cmsg = CMSG_FIRSTHDR(&msg);
@@ -799,6 +816,7 @@
 		cmsg->cmsg_level = SOL_SOCKET;
 		cmsg->cmsg_type = SCM_RIGHTS;
 		*(int *)CMSG_DATA(cmsg) = buf0->fd;
+#endif
 	}
 
  again:
@@ -911,11 +929,15 @@
 msgbuf_read(int fd, struct msgbuf *msgbuf)
 {
 	struct msghdr		 msg;
+#ifdef __sgi
+	int			 sgi_fds[1];
+#else
 	struct cmsghdr		*cmsg;
 	union {
 		struct cmsghdr hdr;
 		char	buf[CMSG_SPACE(sizeof(int) * 1)];
 	} cmsgbuf;
+#endif
 	struct iovec		 iov;
 	ssize_t			 n;
 	int			 fdpass = -1;
@@ -926,14 +948,22 @@
 	}
 
 	memset(&msg, 0, sizeof(msg));
+#ifndef __sgi
 	memset(&cmsgbuf, 0, sizeof(cmsgbuf));
+#endif
 
 	iov.iov_base = msgbuf->rbuf + msgbuf->roff;
 	iov.iov_len = IBUF_READ_SIZE - msgbuf->roff;
 	msg.msg_iov = &iov;
 	msg.msg_iovlen = 1;
+#ifdef __sgi
+	sgi_fds[0] = -1;
+	msg.msg_accrights = (caddr_t)sgi_fds;
+	msg.msg_accrightslen = sizeof(sgi_fds);
+#else
 	msg.msg_control = &cmsgbuf.buf;
 	msg.msg_controllen = sizeof(cmsgbuf.buf);
+#endif
 
 again:
 	if ((n = recvmsg(fd, &msg, 0)) == -1) {
@@ -956,6 +986,11 @@
 
 	msgbuf->roff += n;
 
+#ifdef __sgi
+	/* msg_accrightslen now says how many bytes of descriptors arrived. */
+	if (msg.msg_accrightslen == sizeof(sgi_fds) && sgi_fds[0] != -1)
+		fdpass = sgi_fds[0];
+#else
 	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL;
 	    cmsg = CMSG_NXTHDR(&msg, cmsg)) {
 		if (cmsg->cmsg_level == SOL_SOCKET &&
@@ -979,6 +1014,7 @@
 		}
 		/* we do not handle other ctl data level */
 	}
+#endif
 
 	/* new data arrived, try to process it */
 	return (ibuf_read_process(msgbuf, fdpass));
