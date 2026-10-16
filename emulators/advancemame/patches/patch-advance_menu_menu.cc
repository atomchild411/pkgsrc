$NetBSD$

IRIX's <sys/types.h> has a cell_t typedef; this file defines a struct by the name.

--- advance/menu/menu.cc.orig
+++ advance/menu/menu.cc
@@ -31,6 +31,11 @@
 #include <iomanip>
 #include <algorithm>
 
+// IRIX's <sys/types.h> has a cell_t (a typedef of short).
+#ifdef __sgi
+#define cell_t advance_cell_t
+#endif
+
 using namespace std;
 
 // ------------------------------------------------------------------------
