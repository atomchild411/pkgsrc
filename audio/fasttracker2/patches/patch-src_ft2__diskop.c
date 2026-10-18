$NetBSD$

IRIX: no d_type in struct dirent: take the stat() path for every entry.

--- src/ft2_diskop.c.orig
+++ src/ft2_diskop.c
@@ -1415,14 +1415,18 @@
 
 	searchRec->filesize = 0;
 
-#if defined(__sun) || defined(sun)
+#if defined(__sgi)
+	searchRec->isDir = false; /* no d_type: stat() below says */
+#elif defined(__sun) || defined(sun)
 	stat(fData->d_name, &s);
 	searchRec->isDir = (s.st_mode != S_IFDIR) ? true : false;
 #else
 	searchRec->isDir = (fData->d_type == DT_DIR) ? true : false;
 #endif
 
-#if defined(__sun) || defined(sun)
+#if defined(__sgi)
+	if (1)
+#elif defined(__sun) || defined(sun)
 	if (s.st_mode == S_IFLNK)
 #else
 	if (fData->d_type == DT_UNKNOWN || fData->d_type == DT_LNK)
@@ -1498,14 +1502,18 @@
 
 	searchRec->filesize = 0;
 
-#if defined(__sun) || defined(sun)
+#if defined(__sgi)
+	searchRec->isDir = false; /* no d_type: stat() below says */
+#elif defined(__sun) || defined(sun)
 	stat(fData->d_name, &s);
 	searchRec->isDir = (s.st_mode != S_IFDIR) ? true : false;
 #else
 	searchRec->isDir = (fData->d_type == DT_DIR) ? true : false;
 #endif
 
-#if defined(__sun) || defined(sun)
+#if defined(__sgi)
+	if (1)
+#elif defined(__sun) || defined(sun)
 	if (s.st_mode == S_IFLNK)
 #else
 	if (fData->d_type == DT_UNKNOWN || fData->d_type == DT_LNK)
