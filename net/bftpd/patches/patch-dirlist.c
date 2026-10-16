$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry to skip FIFOs.

--- dirlist.c.orig
+++ dirlist.c
@@ -284,9 +284,17 @@ void dirlist(char *name, FILE *client, c
 
         while ((dir_entry = readdir(directory)) != NULL)
         {
-#ifndef __minix
+#if !defined(__minix) && defined(DT_FIFO)
             if (dir_entry->d_type == DT_FIFO)
                 continue;
+#elif !defined(__minix)
+            /* No d_type (e.g. IRIX): lstat() the entry; cwd is the listed dir. */
+            {
+                struct stat statbuf;
+                if (lstat(dir_entry->d_name, &statbuf) == 0 &&
+                    S_ISFIFO(statbuf.st_mode))
+                    continue;
+            }
 #endif
             can_see_file = fopen(dir_entry->d_name, "r");
             if (can_see_file)
