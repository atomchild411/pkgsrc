$NetBSD$

No d_type in IRIX struct dirent: stat instead.
IRIX: no d_type in struct dirent (stat instead); no tm_gmtoff in struct tm.

--- src/rcsclean.c.orig
+++ src/rcsclean.c
@@ -25,6 +25,8 @@
  */
 
 #include <sys/types.h>
+#include <sys/stat.h>
+#include <sys/stat.h>
 
 #include <dirent.h>
 #include <err.h>
@@ -108,8 +110,28 @@
 		}
 
 		while ((dp = readdir(dirp)) != NULL) {
+#ifdef DT_DIR
+#ifdef DT_DIR
 			if (dp->d_type == DT_DIR)
 				continue;
+#else
+			{
+				struct stat st;
+
+				if (stat(dp->d_name, &st) == 0 &&
+				    S_ISDIR(st.st_mode))
+					continue;
+			}
+#endif
+#else
+			{
+				struct stat st;
+
+				if (stat(dp->d_name, &st) == 0 &&
+				    S_ISDIR(st.st_mode))
+					continue;
+			}
+#endif
 			rcsclean_file(dp->d_name, rev_str);
 		}
 
