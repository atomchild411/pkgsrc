$NetBSD$

IRIX: declare environ; include xmalloc.h for xasprintf.

--- compat/setenv.c.orig
+++ compat/setenv.c
@@ -19,9 +19,20 @@
 
 #include <stdlib.h>
 #include <string.h>
+#include <unistd.h>
 
 #include "compat.h"
+/* xasprintf lives here and compat.h does not pull it in. This file is only
+ * compiled on systems without setenv(), which is rare enough that the missing
+ * include went unnoticed upstream. */
+#include "xmalloc.h"
 
+#ifdef __sgi
+/* IRIX declares environ in no standard header (libc exports it as _environ,
+ * with environ as a weak alias), so declare it the traditional way. */
+extern char **environ;
+#endif
+
 int
 setenv(const char *name, const char *value, __unused int overwrite)
 {
