$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry.

--- util.c.orig
+++ util.c
@@ -145,6 +145,12 @@ int find_file_next(FindFileState *s, cha
             char tmppath[MAX_FILENAME_SIZE];
             makepath(tmppath, sizeof(tmppath), s->dirpath, dirent->d_name);
             isdir = is_directory(tmppath);
+#elif !defined(DT_DIR)
+            // No d_type (e.g. IRIX): lstat() the entry, like d_type
+            char tmppath[MAX_FILENAME_SIZE];
+            struct stat st;
+            makepath(tmppath, sizeof(tmppath), s->dirpath, dirent->d_name);
+            isdir = (!lstat(tmppath, &st) && S_ISDIR(st.st_mode));
 #else
             isdir = (dirent->d_type == DT_DIR);
 #endif
