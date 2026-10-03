$NetBSD$

IRIX has no futimens (it cannot set a descriptor's times): set the times
by name, as tdb used to.

--- common/transaction.c.orig
+++ common/transaction.c
@@ -1206,7 +1206,12 @@
 	   not be backed up (as tdb rounding to block sizes means that
 	   file size changes are quite rare too). The following forces
 	   mtime changes when a transaction completes */
+#if defined(__sgi)
+	/* IRIX has no futimens: set the times by name, as tdb used to. */
+	utimes(tdb->name, NULL);
+#else
 	futimens(tdb->fd, NULL);
+#endif
 
 	/* use a transaction cancel to free memory and remove the
 	   transaction locks */
