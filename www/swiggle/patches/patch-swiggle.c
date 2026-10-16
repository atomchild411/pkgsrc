$NetBSD$

Where struct dirent has no d_type (IRIX), use the existing NO_D_TYPE
stat() code. Keep album names in a struct of our own instead of copies
of struct dirent, whose d_name is only one byte long on IRIX and Solaris.

--- swiggle.c.orig
+++ swiggle.c
@@ -58,6 +58,23 @@
 
 #include "swiggle.h"
 
+/* No d_type in struct dirent (e.g. IRIX): stat() the entries instead. */
+#if !defined(NO_D_TYPE) && !defined(DT_DIR)
+#define NO_D_TYPE
+#endif
+
+/*
+ * Album directory entries are kept here rather than as copies of
+ * struct dirent, which on some systems (IRIX, Solaris) has only a
+ * one-byte d_name and the name is stored past the end of the struct.
+ */
+struct album {
+	char		*d_name;
+#ifndef NO_D_TYPE
+	unsigned char	 d_type;
+#endif
+};
+
 /*
  * Global variables.
  */
@@ -106,7 +123,8 @@ main(int argc, char **argv)
 {
 	char buf[MAXPATHLEN], *eptr, final[MAXPATHLEN], tmp[MAXPATHLEN];
 	int albumcount, i, imgcount;
-	struct dirent *albums, *dent;
+	struct album *albums;
+	struct dirent *dent;
 	struct stat sb;
 	time_t now;
 	DIR *topdir;
@@ -244,13 +262,20 @@ main(int argc, char **argv)
 
 	/* Read in the directory contents and sort by filename. */
 	while ((dent = readdir(topdir)) != NULL) {
-		albums = realloc(albums, (albumcount+1)* sizeof(struct dirent));
+		albums = realloc(albums, (albumcount+1)* sizeof(struct album));
 		if (albums == NULL) {
 			fprintf(stderr, "%s: can't realloc: %s\n", progname, 
 			    strerror(errno));
 			exit(EXIT_FAILURE);
 		}
-		memcpy(&albums[albumcount], dent, sizeof(struct dirent));
+		if ((albums[albumcount].d_name = strdup(dent->d_name)) == NULL) {
+			fprintf(stderr, "%s: can't strdup(%s): %s\n", progname,
+			    dent->d_name, strerror(errno));
+			exit(EXIT_FAILURE);
+		}
+#ifndef NO_D_TYPE
+		albums[albumcount].d_type = dent->d_type;
+#endif
 		albumcount++;
 	}
 	
@@ -260,7 +285,7 @@ main(int argc, char **argv)
 		exit(EXIT_FAILURE);
 	}
 	
-	qsort(albums, albumcount, sizeof(struct dirent), sort_dirs);
+	qsort(albums, albumcount, sizeof(struct album), sort_dirs);
 
 	/* Process each subdirectory (== "album"). */
 	for (i = 0; i < albumcount; i++) {
@@ -284,6 +309,8 @@ main(int argc, char **argv)
 
 	fprintf(html, "</ul>\n%s</body>\n</html>\n", generated);
 
+	for (i = 0; i < albumcount; i++)
+		free(albums[i].d_name);
 	free(albums);
 	
 	if (fclose(html) == EOF) {
@@ -1047,7 +1074,7 @@ sort_by_filesize(const void *a, const vo
 int 
 sort_dirs(const void *a, const void *b)
 {
-	const struct dirent *x, *y;
+	const struct album *x, *y;
 	
 	x = a;
 	y = b;
