$NetBSD$

IRIX has no d_type in struct dirent; rely on the stat() result there.

--- src/font.c.orig
+++ src/font.c
@@ -600,7 +600,7 @@ static void font_dir_search(FT_Library *
 
 		if (stat(full_name, &sc.buf) < 0) continue;	// Get file details
 
-#ifdef WIN32
+#if defined(WIN32) || !defined(DT_DIR)
 		if (S_ISDIR(sc.buf.st_mode))
 #else
 		if ((ep->d_type == DT_DIR) || S_ISDIR(sc.buf.st_mode))
