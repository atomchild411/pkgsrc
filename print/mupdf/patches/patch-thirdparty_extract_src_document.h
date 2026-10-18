$NetBSD$

IRIX's <sys/types.h> defines cell_t.

--- thirdparty/extract/src/document.h.orig
+++ thirdparty/extract/src/document.h
@@ -7,6 +7,10 @@
 #include "compat_stdint.h"
 #include <assert.h>
 
+/* IRIX's <sys/types.h> has a cell_t of its own: have it first, then rename ours. */
+#include <sys/types.h>
+#define cell_t extract_cell_t
+
 typedef struct span_t span_t;
 typedef struct line_t line_t;
 typedef struct paragraph_t paragraph_t;
