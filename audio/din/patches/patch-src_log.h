$NetBSD$

IRIX <math.h> maps flog to logf: undefine it (math.h is include-guarded, so it stays undefined).

--- src/log.h.orig
+++ src/log.h
@@ -9,6 +9,8 @@
 #define __LOG__
 
 #include <fstream>
+#include <math.h>
+#undef flog	// IRIX <math.h>: flog is logf
 using namespace std;
 extern string flog;
 extern ofstream dlog;
