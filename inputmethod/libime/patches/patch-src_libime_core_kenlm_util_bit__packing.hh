$NetBSD$

IRIX has BYTE_ORDER in <endian.h>, and no <arpa/nameser_compat.h>.

--- src/libime/core/kenlm/util/bit_packing.hh.orig
+++ src/libime/core/kenlm/util/bit_packing.hh
@@ -21,7 +21,7 @@
 #include <cassert>
 #ifdef __APPLE__
 #include <architecture/byte_order.h>
-#elif __linux__
+#elif defined(__linux__) || defined(__sgi)
 #include <endian.h>
 #elif !defined(_WIN32) && !defined(_WIN64)
 #include <arpa/nameser_compat.h>
