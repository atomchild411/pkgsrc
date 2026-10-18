$NetBSD$

IRIX: major()/minor() from <sys/mkdev.h>; processors from sysconf; no lutimes (utimensat).

--- mksquashfs.c.orig
+++ mksquashfs.c
@@ -53,6 +53,8 @@
 #include <sys/sysinfo.h>
 #include <sys/sysmacros.h>
 #include <sched.h>
+#elif defined(__sgi)
+#include <sys/mkdev.h>
 #else
 #include <sys/sysctl.h>
 #endif
@@ -5257,6 +5259,8 @@
 			processors = sysconf(_SC_NPROCESSORS_ONLN);
 		else
 			processors = CPU_COUNT(&cpu_set);
+#elif defined(__sgi)
+		processors = sysconf(_SC_NPROCESSORS_ONLN);
 #else
 		int mib[2];
 		size_t len = sizeof(processors);
