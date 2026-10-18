$NetBSD$

IRIX: <sys/fcntl.h> defines OP_NONE (an oplock state).

--- src/ops.h.orig
+++ src/ops.h
@@ -21,6 +21,9 @@
 
 #include "io/ioeta.h"
 
+#ifdef OP_NONE	/* IRIX <sys/fcntl.h>: an oplock state */
+#undef OP_NONE
+#endif
 /* Kinds of operations on files. */
 typedef enum
 {
