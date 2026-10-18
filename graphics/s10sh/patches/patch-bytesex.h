$NetBSD$

Also use the compiler-predefined __BYTE_ORDER__ (IRIX has no _BIG_ENDIAN).

--- bytesex.h.orig
+++ bytesex.h
@@ -13,6 +13,10 @@
 #define BYTE_ORDER_LITTLE_ENDIAN
 #elif defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && (__BYTE_ORDER == _BIG_ENDIAN)
 #define BYTE_ORDER_BIG_ENDIAN
+#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
+#define BYTE_ORDER_LITTLE_ENDIAN
+#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
+#define BYTE_ORDER_BIG_ENDIAN
 #else
 #error can not find the byte order for this architecture, fix bytesex.h
 #endif
