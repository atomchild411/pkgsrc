$NetBSD$

IRIX: no d_type in struct dirent (as AIX, Solaris, QNX); no futimens
(the times are set by path after the close); RAM size from sysconf as on
Solaris (no Linux sysinfo).

--- CPP/Windows/System.cpp.orig
+++ CPP/Windows/System.cpp
@@ -340,7 +340,7 @@
     #if defined(_SC_AIX_REALMEM) // AIX
       size64 = (UInt64)sysconf(_SC_AIX_REALMEM) * 1024;
     #endif
-  #elif 0 || defined(__sun)
+  #elif 0 || defined(__sun) || defined(__sgi)
     #if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
     // FreeBSD, Linux, OpenBSD, and Solaris.
     {
