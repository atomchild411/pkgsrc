$NetBSD$

IRIX has no sun_len.

--- check_milter.c.orig
+++ check_milter.c
@@ -69,7 +69,9 @@
 		fatal(STATE_UNKNOWN, "UNKOWN: socket patch too long: \"%s\"\n",
 		      path);
 
+#ifndef __sgi	/* no sun_len on IRIX */
 	sun.sun_len = SUN_LEN(&sun);
+#endif
 	sun.sun_family = AF_LOCAL;
 	strcpy(sun.sun_path, path);
 
