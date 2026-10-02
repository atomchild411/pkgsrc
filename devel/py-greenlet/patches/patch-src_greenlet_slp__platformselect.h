$NetBSD$

IRIX n32 uses the same MIPS calling convention as Linux.

--- src/greenlet/slp_platformselect.h.orig
+++ src/greenlet/slp_platformselect.h
@@ -52,7 +52,7 @@
 # else
 #  include "platform/switch_arm32_gcc.h" /* gcc using arm32 */
 # endif
-#elif defined(__GNUC__) && defined(__mips__) && defined(__linux__)
+#elif defined(__GNUC__) && defined(__mips__) && (defined(__linux__) || defined(__sgi))
 # include "platform/switch_mips_unix.h" /* Linux/MIPS */
 #elif defined(__GNUC__) && defined(__aarch64__)
 # include "platform/switch_aarch64_gcc.h" /* Aarch64 ABI */
