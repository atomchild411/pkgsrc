$NetBSD$

IRIX: in SGI mode WEXITSTATUS reads its argument through its address
(for union wait), which a constant does not have.

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
