$NetBSD$

Take the byte order from the compiler on systems the list above does not
know (IRIX), instead of assuming little-endian.

--- bytes.h.orig
+++ bytes.h
@@ -71,6 +71,15 @@
 #define __BIG_ENDIAN	4321
 #endif
 
+#if !defined(__BYTE_ORDER) && defined(__BYTE_ORDER__)
+// the compiler's, for systems not listed above (IRIX)
+#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
+#define __BYTE_ORDER	__BIG_ENDIAN
+#else
+#define __BYTE_ORDER	__LITTLE_ENDIAN
+#endif
+#endif
+
 #ifndef __BYTE_ORDER
 #warning "Byte order not defined on your system, assuming little endian!"
 #define __BYTE_ORDER	__LITTLE_ENDIAN
