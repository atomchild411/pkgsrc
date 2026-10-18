$NetBSD$

IRIX's <sys/types.h> defines cell_t.

--- source/fitz/stext-table.c.orig
+++ source/fitz/stext-table.c
@@ -24,6 +24,12 @@
 
 #include <assert.h>
 
+/* IRIX's <sys/types.h> has a cell_t of its own. */
+#define cell_t fz_stext_table_cell_t
+
+/* IRIX's <sys/types.h> has a cell_t of its own. */
+#define cell_t fz_stext_table_cell_t
+
 /* #define DEBUG_WRITE_AS_PS */
 
 /* #define DEBUG_TABLE_STRUCTURE */
