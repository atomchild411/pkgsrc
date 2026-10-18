$NetBSD$

fcntl() is declared in <fcntl.h> (IRIX <sys/fcntl.h> only has the constants).

--- ggrab.cpp.orig
+++ ggrab.cpp
@@ -30,6 +30,7 @@
 #endif
 #include <sys/socket.h>
 #include <sys/fcntl.h>
+#include <fcntl.h>
 #include "cbuffer.h"
 #include "tools.h"
 #include "list.h"
