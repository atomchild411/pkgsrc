$NetBSD$

IRIX support: psutil/_psirix.py, psutil/_psutil_irix.c and psutil/arch/irix/ (files/).

--- psutil/arch/posix/init.c.orig
+++ psutil/arch/posix/init.c
@@ -101,7 +101,7 @@
         return -1;
 
 #if defined(PSUTIL_BSD) || defined(PSUTIL_OSX) || defined(PSUTIL_SUNOS) \
-    || defined(PSUTIL_AIX)
+    || defined(PSUTIL_AIX) || defined(PSUTIL_IRIX)
     if (PyModule_AddIntConstant(mod, "AF_LINK", AF_LINK))
         return -1;
 #endif
