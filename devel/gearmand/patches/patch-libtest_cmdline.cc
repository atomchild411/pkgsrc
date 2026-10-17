$NetBSD$

IRIX declares environ in <unistd.h>: use it (not a private NULL one).

--- libtest/cmdline.cc.orig
+++ libtest/cmdline.cc
@@ -61,7 +61,7 @@
 #include <algorithm>
 #include <stdexcept>
 
-#ifndef __USE_GNU
+#if !defined(__USE_GNU) && !defined(__sgi)
 static char **environ= NULL;
 #endif
 
