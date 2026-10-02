$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Build LLVM, clang and lld to run on IRIX

--- include/llvm/ADT/bit.h.orig
+++ include/llvm/ADT/bit.h
@@ -34,6 +34,9 @@
 #include <endian.h>
 #elif defined(_AIX)
 #include <sys/machine.h>
+#elif defined(__sgi)
+#include <standards.h>
+#include <sys/endian.h>
 #elif defined(__sun)
 /* Solaris provides _BIG_ENDIAN/_LITTLE_ENDIAN selector in sys/types.h */
 #include <sys/types.h>
