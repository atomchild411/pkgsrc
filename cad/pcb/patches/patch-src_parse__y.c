$NetBSD$

IRIX <sys/param.h> defines NOFILE.

--- src/parse_y.c.orig
+++ src/parse_y.c
@@ -130,6 +130,7 @@
 static	LibraryMenuType	*Menu;
 static	bool			LayerFlag[MAX_ALL_LAYER];
 
+#undef NOFILE /* IRIX <sys/param.h> */
 enum FileType {NOFILE=0, PCBFILE, DATAFILE, FONTFILE} file_type;
 
 extern	char		*yytext;		/* defined by LEX */
