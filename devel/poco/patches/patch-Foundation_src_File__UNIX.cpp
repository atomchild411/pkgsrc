$NetBSD: patch-Foundation_src_File__UNIX.cpp,v 1.1 2026/07/24 12:15:52 adam Exp $

Support NetBSD.
IRIX: statvfs (its statfs() takes four arguments).

--- Foundation/src/File_UNIX.cpp.orig
+++ Foundation/src/File_UNIX.cpp
@@ -26,7 +26,7 @@
 #if defined(POCO_OS_FAMILY_BSD)
 #include <sys/param.h>
 #include <sys/mount.h>
-#elif (POCO_OS == POCO_OS_SOLARIS) || (POCO_OS == POCO_OS_QNX)
+#elif (POCO_OS == POCO_OS_SOLARIS) || (POCO_OS == POCO_OS_QNX) || (POCO_OS == POCO_OS_IRIX)
 #include <sys/statvfs.h>
 #else
 #include <sys/statfs.h>
@@ -38,7 +38,7 @@
 #include <utime.h>
 #include <cstring>
 
-#if (POCO_OS == POCO_OS_SOLARIS) || (POCO_OS == POCO_OS_QNX)
+#if (POCO_OS == POCO_OS_SOLARIS) || (POCO_OS == POCO_OS_QNX) || (POCO_OS == POCO_OS_NET_BSD) || (POCO_OS == POCO_OS_IRIX)
 #define STATFSFN ::statvfs
 #define STATFSSTRUCT statvfs
 #else
