$NetBSD: patch-libgphoto2__port_gphoto2_gphoto2-port-portability.h,v 1.1 2018/01/31 10:53:40 jperkin Exp $

Set _XOPEN_SOURCE / _POSIX_C_SOURCE correctly.
IRIX: its default (SGI) mode has usleep and nanosleep; X/Open or POSIX mode would hide the BSD tty ioctls (TIOCM_*) serial/unix.c needs.

--- libgphoto2_port/gphoto2/gphoto2-port-portability.h.orig
+++ libgphoto2_port/gphoto2/gphoto2-port-portability.h
@@ -88,7 +88,9 @@
 
 /* XOPEN needed for usleep */
 #ifndef _XOPEN_SOURCE
+# if (!defined(__sun) || (__STDC_VERSION__-0 < 199901L)) && !defined(__sgi)
 # define _XOPEN_SOURCE 500
+# endif
 #else
 # if ((_XOPEN_SOURCE - 0) < 500)
 #  undef _XOPEN_SOURCE
@@ -98,7 +100,9 @@
 
 /* for nanosleep */
 # ifndef _POSIX_C_SOURCE
+#  if (!defined(__sun) || (__STDC_VERSION__-0 < 199901L)) && !defined(__sgi)
 #  define _POSIX_C_SOURCE 199309
+#  endif
 # endif
 # include <time.h>
 
