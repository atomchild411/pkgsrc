$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry.

--- src/system/filesystem_stdc.cpp.orig
+++ src/system/filesystem_stdc.cpp
@@ -42,6 +42,8 @@
 
 #if defined(UNIX) || defined(HAIKU)
 #include <dirent.h>
+#include <sys/types.h>
+#include <sys/stat.h>
 #endif
 
 CharBuffer* StandardFilesystem::ListDirectory(const char* path)
@@ -92,6 +94,25 @@ CharBuffer* StandardFilesystem::ListDire
 
 #if defined(HAIKU)
         type = TXTLISTDIRTUNKNOWN;
+#elif !defined(DT_DIR)
+        // No d_type in struct dirent (e.g. IRIX): lstat() the entry instead
+        CharBuffer *entrypath = new CharBuffer();
+        entrypath->EnsureSize(StrLen(pathbuf->GetString()) + StrLen(entry->d_name) + 2);
+        entrypath->Empty();
+        entrypath->Append(pathbuf->GetString());
+        entrypath->Append("/");
+        entrypath->Append(entry->d_name);
+        struct stat st;
+        if (lstat(entrypath->GetString(), &st) != 0) {
+            type = TXTLISTDIRTUNKNOWN;
+        } else if (S_ISREG(st.st_mode)) {
+            type = TXTLISTDIRTFILE;
+        } else if (S_ISDIR(st.st_mode)) {
+            type = TXTLISTDIRTDIR;
+        } else {
+            type = TXTLISTDIRTUNKNOWN;
+        }
+        delete entrypath;
 #else
         switch (entry->d_type) {
         case DT_REG:
