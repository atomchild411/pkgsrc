$NetBSD$

IRIX: no d_type, ALLPERMS or TCP keepalive names.

--- res/res_crypto.c.orig
+++ res/res_crypto.c
@@ -786,10 +786,12 @@
 			if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
 				continue;
 			}
+#ifndef __sgi	/* IRIX's struct dirent has no d_type */
 			if (ent->d_type != DT_REG) {
 				ast_log(LOG_WARNING, "Non-regular file '%s' in keys directory\n", ent->d_name);
 				continue;
 			}
+#endif
 			try_load_key(ast_config_AST_KEY_DIR, ent->d_name, ifd, ofd, &note);
 		}
 		closedir(dir);
