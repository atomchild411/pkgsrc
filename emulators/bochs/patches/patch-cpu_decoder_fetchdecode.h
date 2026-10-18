$NetBSD$

IRIX: <sys/fcntl.h> defines OP_NONE (an oplock state).

--- cpu/decoder/fetchdecode.h.orig
+++ cpu/decoder/fetchdecode.h
@@ -206,6 +206,9 @@
 #define BX_DISASM_SRC_ORIGIN(desc) (desc & 0xf)
 #define BX_DISASM_SRC_TYPE(desc) (desc >> 4)
 
+#ifdef OP_NONE	/* IRIX <sys/fcntl.h>: an oplock state */
+#undef OP_NONE
+#endif
 const Bit8u OP_NONE = BX_SRC_NONE;
 
 const Bit8u OP_Eb = BX_FORM_SRC(BX_GPR8, BX_SRC_RM);
