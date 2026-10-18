$NetBSD$

IRIX has no TIOCSCTTY: reopen the pty slave as session leader instead (SVR4).

--- st/st.c.orig
+++ st/st.c
@@ -946,10 +946,22 @@
         dup2(s, 0);
         dup2(s, 1);
         dup2(s, 2);
+#ifdef TIOCSCTTY
         if (ioctl(s, TIOCSCTTY, NULL) < 0)
         {
             die("ioctl TIOCSCTTY failed: %s\n", strerror(errno));
         }
+#else
+        /* SVR4: a session leader's next open of a tty makes it the
+           controlling terminal. */
+        {
+            char *tn = ttyname(s);
+            int tfd;
+
+            if (tn != NULL && (tfd = open(tn, O_RDWR)) >= 0)
+                close(tfd);
+        }
+#endif
         if (s > 2)
         {
             close(s);
