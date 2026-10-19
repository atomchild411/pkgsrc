$NetBSD$

IRIX has no TCP_KEEPIDLE, TCP_KEEPINTVL or TCP_KEEPCNT.

--- tcp.c.orig
+++ tcp.c
@@ -116,14 +116,16 @@
                 logerr(errno,"Could not set tcp keepidle");
                 err=-1;
             }
-#else
+#elif defined(TCP_KEEPIDLE)
             if (setsockopt(ift->fd,IPPROTO_TCP,TCP_KEEPIDLE,
                     &ift->shared->keepidle,sizeof(unsigned)) < 0) {
                 logerr(errno,"Could not set tcp keepidle");
                 err=-1;
             }
+#else
+            ;	/* no TCP_KEEPIDLE (IRIX) */
 #endif
-#if !defined (__APPLE__) || __MAC_OS_X_VERSION_MAX_ALLOWED >= 1090
+#if (!defined (__APPLE__) || __MAC_OS_X_VERSION_MAX_ALLOWED >= 1090) && defined(TCP_KEEPINTVL)
         if (ift->shared->keepintvl)
             if (setsockopt(ift->fd,IPPROTO_TCP,TCP_KEEPINTVL,
                     &ift->shared->keepintvl,sizeof(unsigned)) < 0) {
