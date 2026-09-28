$NetBSD$

Big-endian n32/n64 closures: an integer return narrower than ffi_arg is
widened into its 8-byte slot, so its bytes are the last ones; reading at
the slot start returned the high word (0 for small values).

--- src/mips/n32.S.orig
+++ src/mips/n32.S
@@ -520,6 +520,18 @@
 
 #define V1_OFF2		(3  * FFI_SIZEOF_ARG)
 #define V0_OFF2		(2  * FFI_SIZEOF_ARG)
+/* An integer return narrower than ffi_arg is widened into the whole slot
+   (the handler stores an ffi_arg), so on a big-endian machine its bytes
+   are the slot's last ones. */
+#ifdef __MIPSEB__
+#define V0_OFF2_W	(V0_OFF2 + 4)
+#define V0_OFF2_H	(V0_OFF2 + 6)
+#define V0_OFF2_B	(V0_OFF2 + 7)
+#else
+#define V0_OFF2_W	V0_OFF2
+#define V0_OFF2_H	V0_OFF2
+#define V0_OFF2_B	V0_OFF2
+#endif
 
 #define RA_OFF2		(1  * FFI_SIZEOF_ARG)
 #define GP_OFF2		(0  * FFI_SIZEOF_ARG)
@@ -628,27 +640,27 @@
 
 cls_retsint32:
 	bne     v0, FFI_TYPE_SINT32, cls_retsint16
-	lw	v0, V0_OFF2($sp)
+	lw	v0, V0_OFF2_W($sp)
 	b	cls_epilogue
 
 cls_retsint16:
 	bne     v0, FFI_TYPE_SINT16, cls_retuint16
-	lh	v0, V0_OFF2($sp)
+	lh	v0, V0_OFF2_H($sp)
 	b	cls_epilogue
 
 cls_retuint16:
 	bne     v0, FFI_TYPE_UINT16, cls_retsint8
-	lhu	v0, V0_OFF2($sp)
+	lhu	v0, V0_OFF2_H($sp)
 	b	cls_epilogue
 
 cls_retsint8:
 	bne     v0, FFI_TYPE_SINT8, cls_retuint8
-	lb	v0, V0_OFF2($sp)
+	lb	v0, V0_OFF2_B($sp)
 	b	cls_epilogue
 
 cls_retuint8:
 	bne     v0, FFI_TYPE_UINT8, cls_retfloat
-	lbu	v0, V0_OFF2($sp)
+	lbu	v0, V0_OFF2_B($sp)
 	b	cls_epilogue
 
 cls_retfloat:
