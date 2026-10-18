$NetBSD$

va_copy is <stdarg.h>'s (IRIX's <stdio.h> does not bring it in).

--- buf.cpp.orig
+++ buf.cpp
@@ -16,6 +16,7 @@
 #include "buf.h"
 #include <string.h>
 #include <stdio.h>
+#include <stdarg.h>
 #include <ctype.h>
 
 int		glbBufferCount = 0;
