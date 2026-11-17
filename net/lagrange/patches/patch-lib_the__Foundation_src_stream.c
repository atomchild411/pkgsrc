$NetBSD$

Nothing defines iBigEndian, so streams read little-endian data wrongly on
big-endian CPUs (the ZIP signature of resources.lgr never matches). Take it
from the compiler.

--- lib/the_Foundation/src/stream.c.orig
+++ lib/the_Foundation/src/stream.c
@@ -51,6 +51,12 @@
 iLocalDef uint32_t swap32_(uint32_t v) { return (v >> 24) | ((v & 0xff0000) >> 8) | ((v & 0xff00) << 8) | ((v & 0xff) << 24); }
 iLocalDef uint64_t swap64_(uint64_t v) { return swap32_(v >> 32) | ((uint64_t) (swap32_(v & 0xffffffff)) << 32); }
 
+#if !defined (iBigEndian) && defined (__BYTE_ORDER__) && defined (__ORDER_BIG_ENDIAN__)
+#   if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
+#       define iBigEndian
+#   endif
+#endif
+
 #if defined (iBigEndian)
 static uint16_t order16le_(uint16_t v) { return swap16_(v); }
 static uint32_t order32le_(uint32_t v) { return swap32_(v); }
