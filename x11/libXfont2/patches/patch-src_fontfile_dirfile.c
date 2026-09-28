$NetBSD$

Systems without O_NOFOLLOW (IRIX): define it as 0, as fileio.c already
does.

--- src/fontfile/dirfile.c.orig
+++ src/fontfile/dirfile.c
@@ -46,6 +46,10 @@
 #include <errno.h>
 #include <limits.h>
 #include "src/util/replace.h"
+
+#ifndef O_NOFOLLOW
+#define O_NOFOLLOW 0
+#endif
 
 #ifndef O_CLOEXEC
 #define O_CLOEXEC	0
