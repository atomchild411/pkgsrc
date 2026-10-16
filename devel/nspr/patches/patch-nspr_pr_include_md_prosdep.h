$NetBSD$

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/include/md/prosdep.h.orig
+++ nspr/pr/include/md/prosdep.h
@@ -39,6 +39,9 @@
 #elif defined(OPENBSD)
 #include "md/_openbsd.h"
 
+#elif defined(IRIX)
+#include "md/_irix.h"
+
 #elif defined(LINUX) || defined(__GNU__) || defined(__GLIBC__)
 #include "md/_linux.h"
 
