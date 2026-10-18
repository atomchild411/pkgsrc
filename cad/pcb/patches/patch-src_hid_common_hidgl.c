$NetBSD$

SGI's <GL/glu.h> has no _GLUfuncptr, which Mesa's declares.

--- src/hid/common/hidgl.c.orig
+++ src/hid/common/hidgl.c
@@ -62,6 +62,11 @@
 #  error autoconf couldnt find glu.h
 #endif
 
+#ifdef __sgi
+/* SGI's <GL/glu.h> has no _GLUfuncptr, which Mesa's declares. */
+typedef GLvoid (*_GLUfuncptr)();
+#endif
+
 #include "action.h"
 #include "crosshair.h"
 #include "data.h"
