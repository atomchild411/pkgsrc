$NetBSD$

IRIX: arch.h uses perl Config types (int64_t, ...): include <stdint.h>.

--- ctlib/arch.pl.orig
+++ ctlib/arch.pl
@@ -95,6 +95,10 @@
 #ifndef _CTLIB_ARCH_H
 #define _CTLIB_ARCH_H
 
+#if defined(__sgi) /* perl's Config types are int64_t etc. */
+#include <stdint.h>
+#endif
+
 #define ARCH_HAVE_LONG_DOUBLE        $long_double
 #define ARCH_HAVE_LONG_LONG          $long_long
 ENDCFG
