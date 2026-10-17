$NetBSD$

IRIX: in SGI mode WEXITSTATUS reads its argument through its address
(for union wait), which a constant does not have.
utimensat does not mean futimens: IRIX has the first (compiler-rt) and not the second; utime on a port fails with ENOSYS there.

--- libguile/posix.c.orig
+++ libguile/posix.c
@@ -105,8 +105,10 @@
 # else
 #  define W_EXITCODE(ret, sig)   ((ret) << 8 | (sig))
 # endif
+#ifndef __sgi
 verify (WEXITSTATUS (W_EXITCODE (127, 0)) == 127);
 #endif
+#endif
 
 
 #include <signal.h>
@@ -1932,7 +1934,15 @@
       {
         int fd;
         fd = SCM_FPORT_FDES (object);
+#ifdef HAVE_FUTIMENS
         SCM_SYSCALL (rv = futimens (fd, times));
+#else
+        /* utimensat without futimens (IRIX): a port's file has no name
+           to set its times through. */
+        (void) fd;
+        errno = ENOSYS;
+        rv = -1;
+#endif
         scm_remember_upto_here_1 (object);
       }
     else
