$NetBSD$

IRIX: <sys/fcntl.h> defines OP_NONE (an oplock state).

--- fdm.h.orig
+++ fdm.h
@@ -549,6 +549,9 @@
 	AREA_ANY
 };
 
+#ifdef OP_NONE	/* IRIX <sys/fcntl.h>: an oplock state */
+#undef OP_NONE
+#endif
 /* Expression operators. */
 enum exprop {
 	OP_NONE,
