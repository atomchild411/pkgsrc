$NetBSD$

IRIX port (n32, pthreads); NSS dropped its old one.

--- nss/lib/freebl/libcrux/karamel/krml/lowstar_endianness.h.orig
+++ nss/lib/freebl/libcrux/karamel/krml/lowstar_endianness.h
@@ -14,7 +14,7 @@
 /* ... for Linux */
 #if defined(__linux__) || defined(__CYGWIN__) ||              \
     defined(__USE_SYSTEM_ENDIAN_H__) || defined(__GLIBC__) || \
-    defined(ESP_PLATFORM)
+    defined(ESP_PLATFORM) || defined(__sgi)
 #include <endian.h>
 
 /* ... for OSX */
