$NetBSD$

IRIX: big-endian, no byte-order header; use the compiler's byte swaps.

--- lib/src/portable/endian.h.orig
+++ lib/src/portable/endian.h
@@ -207,6 +207,23 @@
 
 #    endif
 
+#elif defined(__sgi)
+
+/* IRIX: big-endian MIPS, no byte-order macros. */
+#    define htobe16(x) (x)
+#    define htobe32(x) (x)
+#    define htobe64(x) (x)
+#    define be16toh(x) (x)
+#    define be32toh(x) (x)
+#    define be64toh(x) (x)
+
+#    define htole16(x) __builtin_bswap16(x)
+#    define htole32(x) __builtin_bswap32(x)
+#    define htole64(x) __builtin_bswap64(x)
+#    define le16toh(x) __builtin_bswap16(x)
+#    define le32toh(x) __builtin_bswap32(x)
+#    define le64toh(x) __builtin_bswap64(x)
+
 #elif defined(__QNXNTO__)
 
 #    include <gulliver.h>
