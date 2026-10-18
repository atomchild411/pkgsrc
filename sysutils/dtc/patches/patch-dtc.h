$NetBSD$

IRIX <sys/types.h> defines cell_t.

--- dtc.h.orig
+++ dtc.h
@@ -49,6 +49,9 @@
 #define PHANDLE_EPAPR	0x2
 #define PHANDLE_BOTH	0x3
 
+/* IRIX's <sys/types.h> has a cell_t (a CPU number): rename dtc's. */
+#include <sys/types.h>
+#define cell_t dtc_cell_t
 typedef uint32_t cell_t;
 
 static inline bool phandle_is_valid(cell_t phandle)
