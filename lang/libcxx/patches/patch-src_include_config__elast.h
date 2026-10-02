$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/include/config_elast.h.orig
+++ src/include/config_elast.h
@@ -43,6 +43,9 @@
 #  define _LIBCPP_ELAST (_sys_nerr - 1)
 #elif defined(_AIX)
 #  define _LIBCPP_ELAST 127
+#elif defined(__sgi)
+// IRIX's errno values run past 1000, for its own subsystems (ENOJOB is 1700).
+#  define _LIBCPP_ELAST 1999
 #else
 // Warn here so that the person doing the libcxx port has an easier time:
 #  warning ELAST for this platform not yet implemented
