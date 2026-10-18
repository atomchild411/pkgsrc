$NetBSD$

Balance the parentheses of the fallback bswap_16 (big-endian hosts without glibc).

--- lib/cpp/src/thrift/protocol/TProtocol.h.orig
+++ lib/cpp/src/thrift/protocol/TProtocol.h
@@ -170,8 +170,8 @@
       | (((n) & 0x0000ff00ul) << 8)  \
       | (((n) & 0x000000fful) << 24) )
 #  define bswap_16(n) \
-      ( (((n) & (static_cast<unsigned short>(0xff00ul)) >> 8)  \
-      | (((n) & (static_cast<unsigned short>(0x00fful)) << 8)  )
+      static_cast<unsigned short>( (((n) & 0xff00u) >> 8) \
+      | (((n) & 0x00ffu) << 8) )
 #  define THRIFT_htolell(n) bswap_64(n)
 #  define THRIFT_letohll(n) bswap_64(n)
 #  define THRIFT_htolel(n) bswap_32(n)
