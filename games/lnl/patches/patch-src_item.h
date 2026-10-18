$NetBSD$

IRIX <sys/types.h> defines inst_t.

--- src/item.h.orig
+++ src/item.h
@@ -998,6 +998,8 @@
 	necklace_kind_t	necklace_kind;
 } acce_t;
 
+/* IRIX's <sys/types.h> has an inst_t (an instruction word). */
+#define inst_t lnl_inst_t
 typedef struct {
 	inst_kind_t	kind;	/* 楽器の種類 */
 	bool_t	flg_limit;	/* 呪歌の対象を限定出来るか */
