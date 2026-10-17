$NetBSD$

INT_MIN and INT_MAX: <limits.h> (glibc's headers bring it in, IRIX's do not).

--- neo/sys/posix/posix_net.cpp.orig
+++ neo/sys/posix/posix_net.cpp
@@ -38,6 +38,7 @@
 #include <sys/ioctl.h>
 #include <sys/uio.h>
 #include <errno.h>
+#include <limits.h>
 #include <sys/select.h>
 #include <net/if.h>
 #include <ifaddrs.h>
