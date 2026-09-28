$NetBSD: patch-glib_glib-unix.c,v 1.2 2026/04/24 08:02:58 mrg Exp $

Fix build on NetBSD.
IRIX: g_unix_fd_query_path() reports G_FILE_ERROR_NOSYS, as on Hurd.

--- glib/glib-unix.c.orig
+++ glib/glib-unix.c
@@ -49,6 +49,7 @@
 #include <fcntl.h>
 #include <stdlib.h>   /* for fdwalk */
 #include <string.h>
+#include <sys/param.h> /* for MAXPATHLEN */
 #include <sys/types.h>
 #include <pwd.h>
 #include <unistd.h>
@@ -983,6 +984,7 @@
 
   return g_strdup (kf.kf_path);
 #elif defined (__APPLE__) || defined (__NetBSD__) || defined (__OpenBSD__)
+# ifdef F_GETPATH
   char file_path[MAXPATHLEN] = {0};
 
   if (fcntl (fd, F_GETPATH, file_path) < 0)
@@ -996,6 +998,11 @@
     }
 
   return g_strdup (file_path);
+# else
+  g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_NOSYS,
+               "g_unix_fd_query_path() not supported");
+  return NULL;
+# endif
 #elif defined (__GNU__)
   /*
    * Hurd allows to open("/dev/fd/%u") to open the very same fd, but it's not
@@ -1006,6 +1013,11 @@
   g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_NOSYS,
                "g_unix_fd_query_path() not supported on HURD");
   return NULL;
+#elif defined (__sgi)
+  /* IRIX has no way to get a path back from a file descriptor. */
+  g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_NOSYS,
+               "g_unix_fd_query_path() not supported on IRIX");
+  return NULL;
 #else
   #error "g_unix_fd_query_path() not supported on this platform"
 #endif
