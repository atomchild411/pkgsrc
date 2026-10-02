$NetBSD$

IRIX's <strings.h> declares bzero, with a size_t length.

--- Modules/selectmodule.c.orig
+++ Modules/selectmodule.c
@@ -54,8 +54,7 @@
 #endif
 
 #ifdef __sgi
-/* This is missing from unistd.h */
-extern void bzero(void *, int);
+#include <strings.h>
 #endif
 
 #ifdef HAVE_SYS_TYPES_H
