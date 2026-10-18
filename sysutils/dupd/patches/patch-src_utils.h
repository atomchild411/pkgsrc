$NetBSD: patch-src_utils.h,v 1.1 2025/02/26 14:03:06 hauke Exp $

Add NetBSD stat/lstat
IRIX: struct stat and lstat.

--- src/utils.h.orig
+++ src/utils.h
@@ -54,6 +54,11 @@
 #define LSTAT lstat
 #endif
 
+#ifdef __NetBSD__
+#define STRUCT_STAT struct stat
+#define LSTAT lstat
+#endif
+
 #ifdef sun
 #define STRUCT_STAT struct stat64
 #define LSTAT lstat64
@@ -63,6 +68,11 @@
 #define STRUCT_STAT struct stat
 #define LSTAT lstat
 #endif
+
+#ifdef __sgi
+#define STRUCT_STAT struct stat
+#define LSTAT lstat
+#endif
 
 struct block_list_entry {
   uint64_t start_pos;
