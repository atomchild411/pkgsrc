$NetBSD$

IRIX 6.5's realpath() does not allocate (POSIX.1-2008's realpath(path,
NULL)); it needs the caller's buffer, and fails on NULL.

--- src/backends/unix/system.c.orig
+++ src/backends/unix/system.c
@@ -27,6 +27,7 @@
 #include <dirent.h>
 #include <dlfcn.h>
 #include <fcntl.h>
+#include <limits.h>
 #include <stdlib.h>
 #include <stdarg.h>
 #include <stdio.h>
@@ -594,16 +595,15 @@
 qboolean
 Sys_Realpath(const char *in, char *out, size_t size)
 {
-	char *converted = realpath(in, NULL);
+	char converted[PATH_MAX];
 
-	if (converted == NULL)
+	if (realpath(in, converted) == NULL)
 	{
 		Com_Printf("Couldn't get realpath for %s\n", in);
 		return false;
 	}
 
 	Q_strlcpy(out, converted, size);
-	free(converted);
 
 	return true;
 }
