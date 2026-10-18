$NetBSD$

IRIX: byte-order conversions from <sys/endian.h> (clang's IRIX wrappers), as on OpenBSD.

--- src/_csrc/portable_endian.h.orig
+++ src/_csrc/portable_endian.h
@@ -90,7 +90,7 @@
 #   define __LITTLE_ENDIAN LITTLE_ENDIAN
 #   define __PDP_ENDIAN    PDP_ENDIAN
 
-#elif defined(__OpenBSD__)
+#elif defined(__OpenBSD__) || defined(__sgi)
 
 #   include <sys/endian.h>
 
