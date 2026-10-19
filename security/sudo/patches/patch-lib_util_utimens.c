$NetBSD$

AT_FDCWD comes from <fcntl.h>, which glibc's <sys/stat.h> includes and IRIX's does not.

--- lib/util/utimens.c.orig
+++ lib/util/utimens.c
@@ -27,6 +27,7 @@
 
 #include <sys/stat.h>
 #include <sys/time.h>
+#include <fcntl.h>
 #include <errno.h>
 #include <time.h>
 #if !defined(HAVE_UTIMES) || defined(HAVE_FUTIME)
