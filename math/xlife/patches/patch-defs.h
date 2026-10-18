$NetBSD$

IRIX <sys/types.h> defines cell_t.

--- defs.h.orig
+++ defs.h
@@ -122,6 +122,9 @@
 #define stoi(c)		((c) - '0')	/* state character to int */
 #define itos(n)		('0' + (n))	/* int to state character */
 
+/* IRIX's <sys/types.h> has a cell_t (a CPU number): rename xlife's. */
+#include <sys/types.h>
+#define cell_t xlife_cell_t
 #if STATEBITS <= 8
 typedef unsigned char	cell_t;		/* allows 256 states per cell */
 #elif STATEBITS <= 16
