$NetBSD$

IRIX's <math.h> declares rand() and srand() as well, and kpathsea includes
it after the macros below: include it first.

--- mem.h.orig
+++ mem.h
@@ -24,6 +24,8 @@
 #define _MEM_H_
 
 #include <stdlib.h>
+/* IRIX declares rand() and srand() in <math.h> too: before the macros. */
+#include <math.h>
 #ifdef HAVE_INTTYPES_H
 # include <inttypes.h>
 #endif
