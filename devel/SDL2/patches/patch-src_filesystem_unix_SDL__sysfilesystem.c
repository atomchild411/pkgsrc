$NetBSD$

SDL_GetBasePath on IRIX: no /proc/self/exe, so take argv[0] from crt1.o's
__Argv (searching $PATH if it has no '/'), as on OpenBSD. Programs that
find their data relative to the executable could not start.

--- src/filesystem/unix/SDL_sysfilesystem.c.orig
+++ src/filesystem/unix/SDL_sysfilesystem.c
@@ -77,7 +77,7 @@
 #endif
 
 
-#if defined(__OPENBSD__)
+#if defined(__OPENBSD__) || defined(__IRIX__)
 static char *search_path_for_binary(const char *bin)
 {
     char *envr = SDL_getenv("PATH");
@@ -204,6 +204,32 @@
     }
 #endif
 
+#if defined(__IRIX__)
+    /* IRIX has no /proc/self/exe. Take argv[0], which crt1.o keeps in
+       __Argv (weak: NULL if the program was not started through it). */
+    if (!retval) {
+        extern char **__Argv __attribute__((weak));
+        const char *arg0 = (&__Argv != NULL && __Argv) ? __Argv[0] : NULL;
+        if (arg0 && *arg0) {
+            char *exe = NULL;
+            char *realpathbuf = (char *)SDL_malloc(PATH_MAX + 1);
+            if (!realpathbuf) {
+                SDL_OutOfMemory();
+                return NULL;
+            }
+            if (SDL_strchr(arg0, '/') == NULL) { /* not a path: look in $PATH */
+                exe = search_path_for_binary(arg0);
+            }
+            if (realpath(exe ? exe : arg0, realpathbuf) != NULL) {
+                retval = realpathbuf;
+            } else {
+                SDL_free(realpathbuf);
+            }
+            SDL_free(exe);
+        }
+    }
+#endif
+
     /* is a Linux-style /proc filesystem available? */
     if (!retval && (access("/proc", F_OK) == 0)) {
         /* !!! FIXME: after 2.0.6 ships, let's delete this code and just
