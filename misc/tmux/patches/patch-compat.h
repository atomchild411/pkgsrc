$NetBSD$

IRIX 6.5: prototypes for osdep-irix.c (strsignal, round, irix_fixfmt), and
socklen_t, IOV_MAX (15: sendmsg rejects MSG_MAXIOVLEN iovecs) and
struct sockaddr_storage, which IRIX 6.5 predates.

--- compat.h.orig
+++ compat.h
@@ -20,6 +20,9 @@
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <sys/uio.h>
+#ifdef __sgi
+#include <sys/socket.h>		/* MSG_MAXIOVLEN, for IOV_MAX below */
+#endif
 
 #include <fnmatch.h>
 #include <limits.h>
@@ -306,7 +309,63 @@
 /* closefrom.c */
 void		 closefrom(int);
 #endif
+
+/* IRIX 6.5 has no strsignal(), though it does export sys_siglist. tmux ships
+ * no compat file for it and configure does not probe for it, so the
+ * implementation lives in osdep-irix.c, which is always compiled for this
+ * platform. */
+#ifdef __sgi
+const char	*irix_fixfmt(const char *, char *, size_t);
+char		*strsignal(int);
+/* IRIX 6.5 libm has rint/floor/trunc but not the C99 round(). */
+double		 round(double);
 
+/* IRIX 6.5 predates RFC 2553 and POSIX-2001 sockets: it has neither
+ * socklen_t nor struct sockaddr_storage, and its socket calls take plain
+ * int * lengths (see getsockopt in <sys/socket.h>), so int is the correct
+ * width here rather than a guess.
+ *
+ * tmux listens on a Unix domain socket, so the storage struct only has to be
+ * large enough for sockaddr_un (108-byte path) and suitably aligned. This is
+ * the classic BSD layout: ss_family stays a direct member so `sa.ss_family`
+ * works without the #define ss_family trick, and the embedded long long
+ * forces 8-byte alignment. */
+/* libevent's installed <event2/event-config.h> also notices IRIX has no
+ * socklen_t and does `#define socklen_t unsigned int`. Whoever gets there
+ * first wins; only define it if libevent has not. (IRIX's own socket calls
+ * take int *, so the two disagree in signedness but not in width.) */
+#ifndef socklen_t
+typedef int socklen_t;
+#endif
+/* IRIX deliberately does not define IOV_MAX at compile time -- <limits.h>
+ * lists it among the X/Open 4 values "available via sysconf/pathconf".
+ *
+ * Be careful which number you pick: the three plausible answers disagree, and
+ * only one of them is right for sendmsg().
+ *
+ *   sysconf(_SC_IOV_MAX)  512   the readv/writev limit
+ *   _XOPEN_IOV_MAX         16   the X/Open guaranteed minimum
+ *   MSG_MAXIOVLEN          16   <sys/socket.h>, and sendmsg rejects >= this
+ *
+ * The socket layer keeps the old BSD test (iovlen >= MSG_MAXIOVLEN -> EINVAL),
+ * so the largest iovec count sendmsg will actually accept is 15. Measured on
+ * 6.5.7: 15 works, 16 gives EINVAL. Using 16 here made every tmux client die
+ * with "server exited unexpectedly" the moment it had more than 15 buffers
+ * queued -- sendmsg failed with EINVAL and imsg reads that as a dead peer. */
+#ifndef IOV_MAX
+#define IOV_MAX (MSG_MAXIOVLEN - 1)
+#endif
+
+/* libevent does NOT provide a replacement sockaddr_storage in its public
+ * headers -- only an internal one -- so this is still needed. */
+struct sockaddr_storage {
+	short		 ss_family;
+	char		 __ss_pad1[6];
+	long long	 __ss_align;
+	char		 __ss_pad2[112];
+};
+#endif
+
 #ifndef HAVE_STRCASESTR
 /* strcasestr.c */
 char		*strcasestr(const char *, const char *);
