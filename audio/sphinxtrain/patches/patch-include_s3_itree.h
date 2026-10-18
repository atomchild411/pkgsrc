$NetBSD$

IRIX <sys/types.h> defines cell_t.

--- include/s3/itree.h.orig
+++ include/s3/itree.h
@@ -62,6 +62,9 @@
 #define NULL_INDEX	(0xffffffff)
 #define NO_ID		(0xffffffff)
 
+/* IRIX's <sys/types.h> has a cell_t (a CPU number): rename this one. */
+#include <sys/types.h>
+#define cell_t s3_cell_t
 typedef struct cell_s {
     cell_id_t id;		/* id of node */
     cell_index_t child;		/* index of first child context */
