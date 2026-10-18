$NetBSD$

IRIX: SGI GLU has no _GLUfuncptr.

--- src/font.c.orig
+++ src/font.c
@@ -31,6 +31,9 @@
 #include <stdlib.h>
 #include <GL/gl.h>
 #include <GL/glu.h>
+#if defined(__sgi) /* SGI's GLU has no _GLUfuncptr */
+typedef void (*_GLUfuncptr)();
+#endif
 #include <regex.h>
 
 #include "vmath.h"
