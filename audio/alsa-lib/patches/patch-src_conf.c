$NetBSD: patch-src_conf.c,v 1.6 2022/07/15 21:17:25 wiz Exp $

* SunOS has no dirent d_type
IRIX: no d_type in the scandir filters; alphasort64.

--- src/conf.c.orig
+++ src/conf.c
@@ -4103,11 +4103,22 @@
 
 static int config_filename_filter(const struct dirent64 *dirent)
 {
+#ifdef __sun
+	struct stat s;
+#endif
 	size_t flen;
 
 	if (dirent == NULL)
 		return 0;
+#ifdef __sun
+	stat(dirent->d_name, &s);
+	if (s.st_mode & S_IFDIR)
+#elif !defined(DT_DIR)
+	/* No d_type (IRIX): a directory named *.conf fails to open later. */
+	if (0)
+#else
 	if (dirent->d_type == DT_DIR)
+#endif
 		return 0;
 
 	flen = strlen(dirent->d_name);
@@ -4158,6 +4169,7 @@
     !defined(__OpenBSD__) && \
     !defined(__DragonFly__) && \
     !defined(__sun) && \
+    !defined(__sgi) && \
     !defined(__ANDROID__) && \
     !defined(__OHOS__)
 #define SORTFUNC	versionsort64
