$NetBSD$

IRIX: include <strings.h> rather than defining index and rindex as
macros; otherwise a later <strings.h> (libX11) has its index/rindex
prototypes rewritten into strchr/strrchr ones.

--- include/X11/Xos.h.orig
+++ include/X11/Xos.h
@@ -60,7 +60,7 @@
  */
 
 # include <string.h>
-# if defined(__SCO__) || defined(__UNIXWARE__) || defined(__sun) || defined(__CYGWIN__) || defined(_AIX) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
+# if defined(__SCO__) || defined(__UNIXWARE__) || defined(__sun) || defined(__CYGWIN__) || defined(_AIX) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__sgi)
 #  include <strings.h>
 # else
 #  ifndef index
