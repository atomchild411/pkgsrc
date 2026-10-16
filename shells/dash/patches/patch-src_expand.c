$NetBSD$

Not every system has d_type in struct dirent (IRIX): there, every entry is
as DT_UNKNOWN is.

--- src/expand.c.orig
+++ src/expand.c
@@ -1730,9 +1730,11 @@ static char *expmeta(char *name, unsigne
 
 		if (*dname == '.' && !matchdot)
 			goto check_int;
+#ifdef DT_UNKNOWN
 		if (c && dp->d_type != DT_DIR && dp->d_type != DT_LNK &&
 		    dp->d_type != DT_UNKNOWN)
 			goto check_int;
+#endif
 		len = strlen(dname) + 1;
 		p = dname;
 		if (!FNMATCH_IS_ENABLED) {
