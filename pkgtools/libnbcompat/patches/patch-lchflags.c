$NetBSD$

IRIX has no chflags(2): fail with ENOSYS as on illumos and Linux.

--- lchflags.c.orig
+++ lchflags.c
@@ -48,7 +48,7 @@
 	if (S_ISLNK(psb.st_mode)) {
 		return 0;
 	}
-#if defined(__illumos__) || defined(__linux__)
+#if defined(__illumos__) || defined(__linux__) || defined(__sgi)
 	errno = (path == NULL ? EINVAL : ENOSYS);
 	return -1;
 #else
