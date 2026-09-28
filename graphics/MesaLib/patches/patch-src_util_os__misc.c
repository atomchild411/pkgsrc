$NetBSD$

IRIX: total memory from sysmp(MP_SAGET, MPSA_RMINFO).

--- src/util/os_misc.c.orig
+++ src/util/os_misc.c
@@ -68,6 +68,9 @@
 #  include <kernel/OS.h>
 #elif DETECT_OS_WINDOWS
 #  include <windows.h>
+#elif DETECT_OS_IRIX
+#  include <unistd.h>
+#  include <sys/sysmp.h>
 #else
 #error unexpected platform in os_sysinfo.c
 #endif
@@ -268,6 +271,13 @@
    ret = GlobalMemoryStatusEx(&status);
    *size = status.ullTotalPhys;
    return (ret == TRUE);
+#elif DETECT_OS_IRIX
+   struct rminfo rmi;
+
+   if (sysmp(MP_SAGET, MPSA_RMINFO, &rmi, sizeof(rmi)) < 0)
+      return false;
+   *size = (uint64_t)rmi.physmem * (uint64_t)getpagesize();
+   return true;
 #else
 #error unexpected platform in os_sysinfo.c
    return false;
