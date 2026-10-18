$NetBSD$

IRIX: <sys/endian.h> (clang's IRIX wrappers) has these.

--- src/websocket.h.orig
+++ src/websocket.h
@@ -68,7 +68,7 @@
 #  define be16toh(x) BE_IN16(x)
 #  define be32toh(x) BE_IN32(x)
 #  define be64toh(x) BE_IN64(x)
-#elif defined(__FreeBSD__) || defined(__NetBSD__)
+#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__sgi)
 #  include <sys/endian.h>
 #elif defined(__OpenBSD__)
 #  include <sys/types.h>
