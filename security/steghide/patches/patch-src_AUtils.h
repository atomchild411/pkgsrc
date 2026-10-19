$NetBSD: patch-src_AUtils.h,v 1.1 2022/04/25 15:01:53 tnn Exp $

avoid ambiguous math functions
IRIX: include <unistd.h> before zlib.h goes into a namespace; <sys/param.h> defines roundup.

--- src/AUtils.h.orig
+++ src/AUtils.h
@@ -24,13 +24,18 @@
 #include <cmath>
 #ifndef log2
 	// this is in an #ifndef because some cmath implementations #define log2 and some not
-#	define log2(x) (log(x) / log(2.0))
+#	define log2(x) (log((double)(x)) / log(2.0))
 #endif
 
 /**
  * \class AUtils
  * \brief provides some generic functions for non-standard arithmetic operations
  **/
+// IRIX <sys/param.h> defines a roundup(x, y) macro.
+#ifdef roundup
+#undef roundup
+#endif
+
 class AUtils {
 	public:
 	/**
