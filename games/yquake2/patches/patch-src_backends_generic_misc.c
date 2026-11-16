$NetBSD$

IRIX: find the executable through crt1.o's __Argv (no /proc/self/exe);
without it the renderers in libexec/yquake2 are not found.

--- src/backends/generic/misc.c.orig
+++ src/backends/generic/misc.c
@@ -49,6 +49,10 @@
 #include <FindDirectory.h>
 #endif
 
+#ifdef __sgi
+#include <stdlib.h> // realpath()
+#endif
+
 #ifndef PATH_MAX
 // this is mostly for windows. windows has a MAX_PATH = 260 #define, but allows
 // longer paths anyway.. this might not be the maximum allowed length, but is
@@ -126,6 +130,17 @@
 
 	// TODO: realpath() ?
 	// TODO: no idea what this is if the executable is in an app bundle
+#elif defined(__sgi)
+	// IRIX has no /proc/self/exe. crt1.o keeps argv in __Argv, and
+	// bin/quake2 starts the binary by its full path.
+	extern char **__Argv;
+
+	if (__Argv == NULL || __Argv[0] == NULL || strchr(__Argv[0], '/') == NULL ||
+		realpath(__Argv[0], exePath) == NULL)
+	{
+		exePath[0] = '\0';
+	}
+
 #elif defined(__HAIKU__)
 	if (find_path(B_APP_IMAGE_SYMBOL, B_FIND_PATH_IMAGE_PATH, NULL, exePath, PATH_MAX) != B_OK)
 	{
