$NetBSD$

IRIX: no d_type in struct dirent; stat() the entry.

--- mx/mx-create-image-cache.c.orig
+++ mx/mx-create-image-cache.c
@@ -28,6 +28,7 @@
 #include <string.h>
 #include <assert.h>
 #include <stdint.h>
+#include <sys/stat.h>
 
 #include <glib.h>
 #include <gdk-pixbuf/gdk-pixbuf.h>
@@ -395,17 +396,17 @@
         break;
       if (entry->d_name[0] == '.')
         continue;
-      if (entry->d_type == DT_DIR && recurse) {
-          char newdir[2*PATH_MAX];
-          sprintf(newdir, "%s/%s", directory, entry->d_name);
-          makecache(newdir, recurse);
-        }
+      /* stat() rather than d_type, which IRIX lacks */
+      char fullpath[2*PATH_MAX];
+      struct stat st;
+      sprintf(fullpath, "%s/%s", directory, entry->d_name);
+      if (stat(fullpath, &st) != 0)
+        continue;
+      if (S_ISDIR(st.st_mode) && recurse)
+        makecache(fullpath, recurse);
 
-      if (entry->d_type == DT_REG) {
-          char fullpath[2*PATH_MAX];
-          sprintf(fullpath, "%s/%s", directory, entry->d_name);
-          do_one_file(fullpath);
-        }
+      if (S_ISREG(st.st_mode))
+        do_one_file(fullpath);
 
     } while (entry);
 
