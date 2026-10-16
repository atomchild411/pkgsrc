$NetBSD$

IRIX port (n32, pthreads); NSS dropped its old one.

--- nss/lib/freebl/verified/karamel/include/krml/lowstar_endianness.h.orig
+++ nss/lib/freebl/verified/karamel/include/krml/lowstar_endianness.h
@@ -12,7 +12,7 @@
 /******************************************************************************/
 
 /* ... for Linux */
-#if defined(__linux__) || defined(__CYGWIN__) || defined (__USE_SYSTEM_ENDIAN_H__) || defined(__GLIBC__)
+#if defined(__linux__) || defined(__CYGWIN__) || defined (__USE_SYSTEM_ENDIAN_H__) || defined(__GLIBC__) || defined(__sgi)
 #  include <endian.h>
 
 /* ... for OSX */
