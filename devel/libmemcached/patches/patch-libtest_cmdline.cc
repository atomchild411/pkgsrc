$NetBSD$

IRIX: <unistd.h> declares environ (clang's IRIX headers, as the BSDs' do), so libtest must not define its own static one.

--- libtest/cmdline.cc.orig
+++ libtest/cmdline.cc
@@ -61,7 +61,7 @@
 #include <algorithm>
 #include <stdexcept>
 
-#ifndef __USE_GNU
+#if !defined(__USE_GNU) && !defined(__sgi)
 static char **environ= NULL;
 #endif
 
