$NetBSD$

IRIX <sys/types.h> defines cell_t.

--- ggiterm.h.orig
+++ ggiterm.h
@@ -68,6 +68,9 @@
 # define wchar_t unsigned int
 #endif
 
+/* IRIX's <sys/types.h> has a cell_t (a CPU number): rename this one. */
+#include <sys/types.h>
+#define cell_t ggiterm_cell_t
 typedef struct {
 	wchar_t	charcode;
 	int	mode;
