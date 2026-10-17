$NetBSD$

IRIX support: psutil/_psirix.py, psutil/_psutil_irix.c and psutil/arch/irix/ (files/).

--- psutil/arch/posix/net.c.orig
+++ psutil/arch/posix/net.c
@@ -43,6 +43,11 @@
 #include <netdb.h>
 #endif
 
+#if defined(PSUTIL_IRIX)
+#include <netdb.h>
+#include <sys/sockio.h>
+#endif
+
 #include "../../arch/all/init.h"
 
 
