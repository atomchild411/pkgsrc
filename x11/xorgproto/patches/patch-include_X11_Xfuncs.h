$NetBSD$

IRIX: include <strings.h> before defining bzero as a macro, as for the
other systems whose <string.h> does not; otherwise a later <strings.h>
(libX11's imDefIm.c) gets its bzero prototype rewritten into memset.

--- include/X11/Xfuncs.h.orig
+++ include/X11/Xfuncs.h
@@ -44,7 +44,7 @@
 #    define bcmp(b1,b2,len) memcmp(b1, b2, len)
 #   else
 #    include <string.h>
-#    if defined(__SCO__) || defined(__sun) || defined(__UNIXWARE__) || defined(__CYGWIN__) || defined(_AIX) || defined(__APPLE__)
+#    if defined(__SCO__) || defined(__sun) || defined(__UNIXWARE__) || defined(__CYGWIN__) || defined(_AIX) || defined(__APPLE__) || defined(__sgi)
 #     include <strings.h>
 #    endif
 #    define _XFUNCS_H_INCLUDED_STRING_H
