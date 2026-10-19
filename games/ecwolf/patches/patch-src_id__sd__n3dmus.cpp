$NetBSD$

IRIX's <sys/types.h> has an inst_t: rename this one.

--- src/id_sd_n3dmus.cpp.orig
+++ src/id_sd_n3dmus.cpp
@@ -13,6 +13,9 @@
 
 bool N3DTempoEmulation;
 
+#include <sys/types.h>
+#define inst_t n3d_inst_t	/* IRIX's <sys/types.h> has an inst_t */
+
 typedef struct
 {
 	byte	mChar,cChar,
