$NetBSD$

IRIX counts processors with sysconf() too.

--- src/lib/eina_cpu.c.orig	2026-10-02 16:01:59.021073676 +0000
+++ src/lib/eina_cpu.c	2026-10-02 16:01:59.025073750 +0000
@@ -24,7 +24,7 @@
 # ifdef _WIN32
 #  define WIN32_LEAN_AND_MEAN
 #  include <windows.h>
-# elif defined (__sun) || defined(__GNU__)
+# elif defined (__sun) || defined(__GNU__) || defined(__sgi)
 #  include <unistd.h>
 # elif defined (__FreeBSD__) || defined (__OpenBSD__) || \
    defined (__NetBSD__) || defined (__DragonFly__) || defined (__MacOSX__) || \
@@ -144,7 +144,7 @@
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
 
-# elif defined (__sun) || defined(__GNU__)
+# elif defined (__sun) || defined(__GNU__) || defined(__sgi)
    /*
     * _SC_NPROCESSORS_ONLN: number of processors that are online, that
                             is available when sysconf is called. The number
