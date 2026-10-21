$NetBSD$

Without d_type in struct dirent (IRIX), tell folders from files by stat(), as on Symbian.

--- lib/warmux/tools/file_tools.cpp.orig
+++ lib/warmux/tools/file_tools.cpp
@@ -275,7 +275,7 @@
 {
   DIR           *dir;
   struct dirent *file;
-#ifdef __SYMBIAN32__
+#if defined(__SYMBIAN32__) || !defined(DT_DIR)
   std::string    dname;
 #endif
 };
@@ -284,7 +284,7 @@
 {
   FolderSearch *f = new FolderSearch;
   f->dir = opendir(dirname.c_str());
-#ifdef __SYMBIAN32__
+#if defined(__SYMBIAN32__) || !defined(DT_DIR)
   f->dname = dirname;
 #endif
 
@@ -302,6 +302,8 @@
 
 #ifdef __SYMBIAN32__
     if (f->file->d_namlen && DoesFolderExist(f->dname+"/"+std::string(f->file->d_name))) {
+#elif !defined(DT_DIR)
+    if (DoesFolderExist(f->dname+"/"+std::string(f->file->d_name))) {
 #else
     if (f->file->d_type == DT_DIR) {
 #endif
@@ -318,6 +320,8 @@
     // This is a file and we do search for file
 #ifdef __SYMBIAN32__
     if (f->file->d_namlen && DoesFileExist(f->dname+"/"+std::string(f->file->d_name))) {
+#elif !defined(DT_DIR)
+    if (DoesFileExist(f->dname+"/"+std::string(f->file->d_name))) {
 #else
     if (f->file->d_type == DT_REG) {
 #endif
