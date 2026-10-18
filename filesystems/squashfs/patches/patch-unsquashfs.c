$NetBSD$

IRIX: major()/minor() from <sys/mkdev.h>; processors from sysconf; no lutimes (utimensat).

--- unsquashfs.c.orig
+++ unsquashfs.c
@@ -36,6 +36,8 @@
 #include <sched.h>
 #include <sys/sysinfo.h>
 #include <sys/sysmacros.h>
+#elif defined(__sgi)
+#include <sys/mkdev.h>
 #else
 #include <sys/sysctl.h>
 #endif
@@ -1251,7 +1253,21 @@
 				goto failed;
 			}
 
+#ifdef __sgi
+			{
+				/* No lutimes on IRIX: utimensat, not following. */
+				struct timespec ts[2];
+
+				ts[0].tv_sec = times[0].tv_sec;
+				ts[0].tv_nsec = times[0].tv_usec * 1000;
+				ts[1].tv_sec = times[1].tv_sec;
+				ts[1].tv_nsec = times[1].tv_usec * 1000;
+				res = utimensat(AT_FDCWD, pathname, ts,
+					AT_SYMLINK_NOFOLLOW);
+			}
+#else
 			res = lutimes(pathname, times);
+#endif
 			if(res == -1) {
 				EXIT_UNSQUASH_STRICT("create_inode: failed to"
 					" set time on %s, because %s\n",
@@ -2775,6 +2791,8 @@
 			processors = sysconf(_SC_NPROCESSORS_ONLN);
 		else
 			processors = CPU_COUNT(&cpu_set);
+#elif defined(__sgi)
+		processors = sysconf(_SC_NPROCESSORS_ONLN);
 #else
 		int mib[2];
 		size_t len = sizeof(processors);
