$NetBSD$

IRIX 6.5 has no O_CLOEXEC (POSIX 2008): open /dev/kmem without it and set
FD_CLOEXEC with fcntl instead.  (From tools/irix-cross/pkg/patches/
make-4.4.1-irix.patch, proven on IRIX with the hand-built gmake.)

--- lib/getloadavg.c.orig
+++ lib/getloadavg.c
@@ -81,6 +81,13 @@
 /* Specification.  */
 #include <stdlib.h>
 
+/* O_CLOEXEC is POSIX-2008; IRIX 6.5 predates it. 0 is gnulib's usual fallback
+   -- the open still works, it simply is not atomically close-on-exec, which
+   the F_SETFD below compensates for. */
+#ifndef O_CLOEXEC
+# define O_CLOEXEC 0
+#endif
+
 #include <errno.h>
 #include <stdio.h>
 
@@ -878,6 +885,12 @@
       int fd = open ("/dev/kmem", O_RDONLY | O_CLOEXEC);
       if (0 <= fd)
         {
+#  if O_CLOEXEC == 0
+          /* No atomic close-on-exec on this system (see the fallback above),
+             so set it explicitly. make forks for every recipe line, and a
+             /dev/kmem descriptor inherited by every child is worth avoiding. */
+          fcntl (fd, F_SETFD, FD_CLOEXEC);
+#  endif
           channel = fd;
           getloadavg_initialized = true;
         }
