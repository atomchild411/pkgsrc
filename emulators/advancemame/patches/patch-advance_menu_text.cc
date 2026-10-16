$NetBSD$

IRIX's <sys/types.h> has a cell_t typedef; this file defines a struct by the name.

--- advance/menu/text.cc.orig
+++ advance/menu/text.cc
@@ -35,6 +35,11 @@
 #include <deque>
 #include <cmath>
 
+// IRIX's <sys/types.h> has a cell_t (a typedef of short).
+#ifdef __sgi
+#define cell_t advance_cell_t
+#endif
+
 using namespace std;
 
 // -------------------------------------------------------------------------
