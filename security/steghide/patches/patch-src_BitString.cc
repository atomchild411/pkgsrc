$NetBSD$

IRIX: include <unistd.h> before zlib.h goes into a namespace; <sys/param.h> defines roundup.

--- src/BitString.cc.orig
+++ src/BitString.cc
@@ -23,6 +23,8 @@
 #include "common.h"
 
 #ifdef USE_ZLIB
+// zconf.h includes <unistd.h>: include it outside the namespace first.
+#include <unistd.h>
 namespace zlib {
 #include <zlib.h>
 }
