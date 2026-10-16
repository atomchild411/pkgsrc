$NetBSD$

Where struct dirent has no d_type (IRIX), scan_target() lstat()s each
entry and ENTRY_ISDIR() uses that mode.

--- include/util.h.orig
+++ include/util.h
@@ -15,7 +15,17 @@
 #define IS_STDOUT_REDIRECT (!isatty(STDOUT_FILENO))
 
 #ifndef _WIN32
+#include <dirent.h>
+#ifdef DT_DIR
 #define ENTRY_ISDIR(e) (e->d_type == DT_DIR)
+#else
+/* No d_type in struct dirent (e.g. IRIX): scan_target() lstat()s each entry
+ * into scan_entry_mode before it is examined (scanning is single-threaded). */
+#include <sys/types.h>
+#include <sys/stat.h>
+extern mode_t scan_entry_mode;
+#define ENTRY_ISDIR(e) ((void)(e), S_ISDIR(scan_entry_mode))
+#endif
 #define IS_PATHSEP(c) (c == '/')
 #else
 #define ENTRY_ISDIR(e) (GetFileAttributes(e->d_name) & FILE_ATTRIBUTE_DIRECTORY)
