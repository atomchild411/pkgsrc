$NetBSD$

IRIX <sys/types.h> defines cell_t.

--- game.h.orig
+++ game.h
@@ -58,6 +58,9 @@
    int y;
 } vector_t;
 
+/* IRIX's <sys/types.h> has a cell_t (a CPU number): rename this one. */
+#include <sys/types.h>
+#define cell_t game2048_cell_t
 typedef struct cell {
    int value;
    vector_t pos;
