$NetBSD$

IRIX: pid_t is long, so declare the hooks with it; no d_type in struct dirent; no tm_zone or tm_gmtoff in struct tm.

--- fetch-maildir.c.orig
+++ fetch-maildir.c
@@ -169,12 +169,14 @@
 		}
 
 		while ((dp = readdir(dirp)) != NULL) {
+#ifdef DT_UNKNOWN	/* no d_type on IRIX: stat every entry */
 			if (dp->d_type == DT_REG) {
 				data->total++;
 				continue;
 			}
 			if (dp->d_type != DT_UNKNOWN)
 				continue;
+#endif
 
 			if (ppath(entry, sizeof entry, "%s/%s", path,
 			    dp->d_name) != 0) {
