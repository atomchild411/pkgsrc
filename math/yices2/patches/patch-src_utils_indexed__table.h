$NetBSD$

IRIX <sys/types.h> has an index_t (short): rename this one.

--- src/utils/indexed_table.h.orig
+++ src/utils/indexed_table.h
@@ -23,6 +23,8 @@
 #include <stdint.h>
 
 /* An index into the table. */
+#include <sys/types.h>
+#define index_t yices_index_t
 typedef int32_t index_t;
 
 /* An unsigned index into the table. */
