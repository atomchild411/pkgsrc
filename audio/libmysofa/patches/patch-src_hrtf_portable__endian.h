$NetBSD$

IRIX: the BSD byte-order macros, from <sys/endian.h>.

--- src/hrtf/portable_endian.h.orig	2026-10-02 14:32:03.520588251 +0000
+++ src/hrtf/portable_endian.h	2026-10-02 14:32:03.524588321 +0000
@@ -41,7 +41,7 @@
 #	define __LITTLE_ENDIAN LITTLE_ENDIAN
 #	define __PDP_ENDIAN    PDP_ENDIAN
 
-#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
+#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__sgi)
 
 #	include <sys/endian.h>
 
