$NetBSD$

IRIX: byte order from <sys/endian.h>, not Solaris's <sys/byteorder.h>.

--- include/X11/Xarch.h.orig	2026-10-02 14:26:21.290571746 +0000
+++ include/X11/Xarch.h	2026-10-02 14:26:21.310572100 +0000
@@ -39,7 +39,10 @@
 
 # else
 
-#  if defined(SVR4) || defined(__SVR4)
+#  if defined(__sgi)
+#   include <sys/types.h>
+#   include <sys/endian.h>
+#  elif defined(SVR4) || defined(__SVR4)
 #   include <sys/types.h>
 #   include <sys/byteorder.h>
 #  elif defined(CSRG_BASED)
@@ -83,6 +86,9 @@
 #     define BYTE_ORDER BIG_ENDIAN
 #    endif
 #   endif /* sun */
+#   if defined(__sgi) && defined(_BYTE_ORDER)
+#    define BYTE_ORDER _BYTE_ORDER
+#   endif /* sgi */
 #  endif /* BYTE_ORDER */
 
 #  define X_BYTE_ORDER BYTE_ORDER
