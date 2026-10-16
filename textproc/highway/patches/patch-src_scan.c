$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry and use
its mode instead of d_type.

--- src/scan.c.orig
+++ src/scan.c
@@ -14,6 +14,11 @@
 #define rindex(x, y) strchr(x, y)
 #endif
 
+#if !defined(_WIN32) && !defined(DT_DIR)
+/* lstat() mode of the entry being examined; see ENTRY_ISDIR in util.h. */
+mode_t scan_entry_mode;
+#endif
+
 /**
  * Add a filename to the queue and launch the sleeping search worker.
  */
@@ -77,7 +82,13 @@ bool is_search_target_by_stat(const stru
 
 bool is_search_target_by_entry(const struct dirent *entry)
 {
-#ifndef _WIN32
+#if !defined(_WIN32) && !defined(DT_DIR)
+    if (op.follow_link) {
+        return S_ISREG(scan_entry_mode) || S_ISLNK(scan_entry_mode);
+    } else {
+        return S_ISREG(scan_entry_mode);
+    }
+#elif !defined(_WIN32)
     if (op.follow_link) {
         return entry->d_type == DT_REG || entry->d_type == DT_LNK;
     } else {
@@ -128,6 +139,13 @@ void scan_target(file_queue *queue, cons
 
     struct dirent *entry;
     while ((entry = readdir(dir)) != NULL) {
+#if !defined(_WIN32) && !defined(DT_DIR)
+        {
+            struct stat st;
+            sprintf(buf, "%s%s", base, entry->d_name);
+            scan_entry_mode = lstat(buf, &st) == 0 ? st.st_mode : 0;
+        }
+#endif
         // `readdir` returns also current or upper directory, but we don't need that directories,
         // so skip them. And also hidden directory doesn't need.
         if (is_skip_entry(entry)) {
@@ -143,7 +161,11 @@ void scan_target(file_queue *queue, cons
 
         // Check if symlink exists. Skip this entry if not exist.
 #ifndef _WIN32
+#ifdef DT_LNK
         if (op.follow_link && entry->d_type == DT_LNK) {
+#else
+        if (op.follow_link && S_ISLNK(scan_entry_mode)) {
+#endif
             char link[MAX_PATH_LENGTH] = { 0 };
             readlink(buf, link, MAX_PATH_LENGTH);
             if (access(link, F_OK) != 0) {
