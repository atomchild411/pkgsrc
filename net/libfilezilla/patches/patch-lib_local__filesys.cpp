$NetBSD$

AT_SYMLINK_NOFOLLOW is in <fcntl.h>.

--- lib/local_filesys.cpp.orig
+++ lib/local_filesys.cpp
@@ -12,6 +12,7 @@
 #include <errno.h>
 #include <limits.h>
 #include <sys/fcntl.h>
+#include <fcntl.h> // AT_SYMLINK_NOFOLLOW (POSIX puts it here)
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
