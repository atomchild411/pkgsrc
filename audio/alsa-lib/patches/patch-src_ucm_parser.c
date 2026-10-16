$NetBSD: patch-src_ucm_parser.c,v 1.9 2021/06/28 10:10:50 wiz Exp $

* SunOS has no dirent d_type
IRIX: no d_type in the scandir filters; alphasort64.

--- src/ucm/parser.c.orig
+++ src/ucm/parser.c
@@ -3655,7 +3655,17 @@
 {
 	if (dirent == NULL)
 		return 0;
+#ifdef __sun
+	struct stat s;
+	stat(dirent->d_name, &s);
+	if (s.st_mode & S_IFDIR) {
+#elif !defined(DT_DIR)
+	/* No d_type (IRIX): take every entry but . and ..; what is not
+	   a card directory fails to load later. */
+	{
+#else
 	if (dirent->d_type == DT_DIR) {
+#endif
 		if (dirent->d_name[0] == '.') {
 			if (dirent->d_name[1] == '\0')
 				return 0;
@@ -3713,6 +3723,7 @@
     !defined(__OpenBSD__) && \
     !defined(__DragonFly__) && \
     !defined(__sun) && \
+    !defined(__sgi) && \
     !defined(__ANDROID__) && \
     !defined(__OHOS__)
 #define SORTFUNC	versionsort64
