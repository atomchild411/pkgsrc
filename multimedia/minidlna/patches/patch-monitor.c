$NetBSD: patch-monitor.c,v 1.1 2018/06/02 12:53:10 jmcneill Exp $

No d_type (IRIX): resolve every entry's type, as scanner.c does.

--- monitor.c.orig
+++ monitor.c
@@ -446,7 +446,7 @@
 			}
 			depth++;
 			strcpy(last_dir, parent_buf);
-			parent_buf = dirname(parent_buf);
+			parent_buf = dirname(last_dir);
 		}
 		while( strcmp(parent_buf, "/") != 0 );
 
@@ -552,6 +552,7 @@
 			continue;
 		esc_name = escape_tag(e->d_name, 1);
 		snprintf(path_buf, sizeof(path_buf), "%s/%s", path, e->d_name);
+#if HAVE_STRUCT_DIRENT_D_TYPE
 		switch( e->d_type )
 		{
 			case DT_DIR:
@@ -562,6 +563,9 @@
 			default:
 				break;
 		}
+#else
+		type = resolve_unknown_type(path_buf, dir_types);
+#endif
 		if( type == TYPE_DIR )
 		{
 			monitor_insert_directory(fd, esc_name, path_buf);
