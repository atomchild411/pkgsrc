$NetBSD: patch-locale.cpp,v 1.2 2024/05/29 17:51:10 adam Exp $

Fix SunOS build.
Fix IRIX build (open() is in <fcntl.h>), as SunOS.

--- locale.cpp.orig
+++ locale.cpp
@@ -28,7 +28,11 @@
 #include <windows.h>
 #else
 #include <unistd.h>
-#include <sys/fcntl.h>
+#  if defined(__sun) || defined(__sgi)
+#    include <fcntl.h>
+#  else
+#    include <sys/fcntl.h>
+#  endif
 #include <sys/stat.h>
 #include <sys/mman.h>
 #endif
