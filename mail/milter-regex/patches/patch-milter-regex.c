$NetBSD$

IRIX: st_mtime as on Linux and Solaris (no st_mtimespec).

--- milter-regex.c.orig
+++ milter-regex.c
@@ -131,7 +131,7 @@
 	{ NULL, NULL }
 };
 
-#if __linux__ || __sun__
+#if __linux__ || __sun__ || __sgi
 #define	ST_MTIME st_mtime
 extern size_t	 strlcpy(char *, const char *, size_t);
 #else
