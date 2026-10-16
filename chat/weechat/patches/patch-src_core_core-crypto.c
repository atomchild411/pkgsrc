$NetBSD$

htobe64 is in <endian.h>, which IRIX's <sys/types.h> does not include.

--- src/core/core-crypto.c.orig
+++ src/core/core-crypto.c
@@ -50,6 +50,9 @@
 #include <ByteOrder.h>
 #define BE_INT64 B_HOST_TO_BENDIAN_INT64
 #else
+#ifdef __sgi
+#include <endian.h>
+#endif
 #define BE_INT64 htobe64
 #endif
 
