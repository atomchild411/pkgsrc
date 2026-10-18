$NetBSD$

IRIX: no d_type or DT_* in <dirent.h>.

--- package/konoha.posix/posix.c.orig
+++ package/konoha.posix/posix.c
@@ -528,6 +528,7 @@
 }
 
 static knh_IntData_t DirConstInt[] = {
+#ifdef DT_UNKNOWN /* IRIX: no d_type */
 	{"DT_UNKNOWN", DT_UNKNOWN},
 	{"DT_FIFO",    DT_FIFO},
 	{"DT_CHR",     DT_CHR},
@@ -537,6 +538,7 @@
 	{"DT_LNK",     DT_LNK},
 	{"DT_SOCK",    DT_SOCK},
 	{"DT_WHT",     DT_WHT},
+#endif
 	{NULL}
 };
 
@@ -589,10 +591,14 @@
 		if(dp != NULL) {
 			mdata = new_DataMap(ctx);
 			knh_DataMap_setString(ctx, mdata, "d_name", dp->d_name);
+#ifdef DT_UNKNOWN
 			knh_DataMap_setInt(ctx, mdata, "d_type", dp->d_type);
+#endif
 			KNH_NTRACE2(ctx, "readdir", K_OK, KNH_LDATA0);
 		} else if (errno != 0) {
+#ifdef DT_UNKNOWN
 			knh_DataMap_setInt(ctx, mdata, "d_type", dp->d_type);
+#endif
 			KNH_NTRACE2(ctx, "readdir", K_PERROR, KNH_LDATA0);
 		} else {
 			KNH_NTRACE2(ctx, "readdir", K_OK, KNH_LDATA0);
