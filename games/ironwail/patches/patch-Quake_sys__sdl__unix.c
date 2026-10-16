$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry to find
directories.

--- Quake/sys_sdl_unix.c.orig
+++ Quake/sys_sdl_unix.c
@@ -665,14 +665,27 @@ typedef struct unixfindfile_s {
 	DIR				*handle;
 	struct dirent	*data;
 	char			filter[8];
+#ifndef DT_DIR
+	char			dir[MAX_OSPATH];	/* no d_type: lstat() each entry */
+#endif
 } unixfindfile_t;
 
 static void Sys_FillFindData (unixfindfile_t *find)
 {
 	q_strlcpy (find->base.name, find->data->d_name, sizeof (find->base.name));
 	find->base.attribs = 0;
+#ifdef DT_DIR
 	if (find->data->d_type & DT_DIR)
 		find->base.attribs |= FA_DIRECTORY;
+#else
+	{
+		char		path[MAX_OSPATH * 2];
+		struct stat	st;
+		q_snprintf (path, sizeof (path), "%s/%s", find->dir, find->data->d_name);
+		if (lstat (path, &st) == 0 && S_ISDIR (st.st_mode))
+			find->base.attribs |= FA_DIRECTORY;
+	}
+#endif
 }
 
 static struct dirent *readdir_filtered (DIR *handle, const char *ext)
@@ -717,6 +730,9 @@ findfile_t *Sys_FindFirst (const char *d
 	ret->handle = handle;
 	ret->data = data;
 	q_strlcpy (ret->filter, ext, sizeof (ret->filter));
+#ifndef DT_DIR
+	q_strlcpy (ret->dir, dir, sizeof (ret->dir));
+#endif
 	Sys_FillFindData (ret);
 
 	return (findfile_t *) ret;
