$NetBSD$

IRIX has no RTLD_NEXT (nor RTLD_DEFAULT): use pthread_create itself, as without dlsym.

--- src/background_thread.c.orig
+++ src/background_thread.c
@@ -61,7 +61,7 @@
 	 * wrapper for pthread_create; and 2) application may define its own
 	 * wrapper as well (and can call malloc within the wrapper).
 	 */
-#	ifdef JEMALLOC_HAVE_DLSYM
+#	if defined(JEMALLOC_HAVE_DLSYM) && defined(RTLD_NEXT)
 	pthread_create_fptr = dlsym(RTLD_NEXT, "pthread_create");
 	if (pthread_create_fptr == NULL) {
 		pthread_create_fptr = dlsym(RTLD_DEFAULT, "pthread_create");
