$NetBSD$

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/src/md/unix/uxrng.c.orig
+++ nspr/pr/src/md/unix/uxrng.c
@@ -26,7 +26,7 @@
 
 #elif (defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD_kernel__) || \
        defined(NETBSD) || defined(__NetBSD_kernel__) || defined(OPENBSD) || \
-       defined(__GNU__))
+       defined(__GNU__) || defined(IRIX))
 #  include <sys/types.h>
 #  include <sys/stat.h>
 #  include <fcntl.h>
