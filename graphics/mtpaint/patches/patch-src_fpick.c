$NetBSD$

IRIX has no d_type in struct dirent; rely on the stat() result there.

--- src/fpick.c.orig
+++ src/fpick.c
@@ -399,7 +399,7 @@ static void scan_dir(fpick_dd *dt, DIR *
 
 		if (!dt->show_hidden && (ep->d_name[0] == '.')) continue;
 
-#ifdef WIN32
+#if defined(WIN32) || !defined(DT_DIR)
 		subdir = S_ISDIR(buf.st_mode);
 #else
 		subdir = (ep->d_type == DT_DIR) || S_ISDIR(buf.st_mode);
