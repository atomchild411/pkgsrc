$NetBSD$

IRIX: realpath(path, NULL) does not allocate the result there, so -fsroot
and -startin always failed ("Failed to resolve argument to -fsroot").

Nor does getcwd(NULL, 0) allocate there, so the default -fsroot (the
current directory) failed the same way.

--- src/ieee.c.orig
+++ src/ieee.c
@@ -110,6 +110,34 @@
 }
 #endif
 
+#ifdef __sgi
+// IRIX's realpath() does not allocate the result when resolved_path is NULL.
+static char *
+x16_realpath(const char *path, char *resolved_path) {
+	char buf[PATH_MAX], *r;
+
+	if (resolved_path != NULL)
+		return realpath(path, resolved_path);
+	if ((r = realpath(path, buf)) == NULL)
+		return NULL;
+	return strdup(r);
+}
+#define realpath x16_realpath
+
+// Nor does getcwd(NULL, 0) allocate one (the default -fsroot and -startin).
+static char *
+x16_getcwd(char *buf, size_t size) {
+	char tmp[PATH_MAX];
+
+	if (buf != NULL)
+		return getcwd(buf, size);
+	if (getcwd(tmp, sizeof(tmp)) == NULL)
+		return NULL;
+	return strdup(tmp);
+}
+#define getcwd x16_getcwd
+#endif
+
 #define u8strchr(A,B) (uint8_t *)strchr((char *)A,B)
 #define u8strrchr(A,B) (uint8_t *)strrchr((char *)A,B)
 #define u8strcpy(A,B) strcpy((char *)A,(char *)B)
