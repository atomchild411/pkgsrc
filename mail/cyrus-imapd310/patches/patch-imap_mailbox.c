$NetBSD$

IRIX: no d_type in struct dirent.

--- imap/mailbox.c.orig
+++ imap/mailbox.c
@@ -6061,11 +6061,13 @@
     dirp = opendir(path);
     if (dirp) {
         while ((f = readdir(dirp))!=NULL) {
+#ifdef DT_DIR /* IRIX: no d_type */
             if (f->d_type == DT_DIR) {
                 /* xunlink() will fail on a directory and create syslog noise.
                    We rmdir() later in mailbox_delete_cleanup() anyways */
                 continue;
             }
+#endif
             if (f->d_name[0] == '.'
                 && (f->d_name[1] == '\0'
                     || (f->d_name[1] == '.' &&
