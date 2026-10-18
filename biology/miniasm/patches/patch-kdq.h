$NetBSD$

A 58-bit field needs a 64-bit type: size_t is 32 bits on ILP32 (IRIX n32).

--- kdq.h.orig
+++ kdq.h
@@ -3,10 +3,11 @@
 
 #include <stdlib.h>
 #include <string.h>
+#include <stdint.h>
 
 #define __KDQ_TYPE(type) \
 	typedef struct { \
-		size_t front:58, bits:6, count, mask; \
+		uint64_t front:58, bits:6; size_t count, mask; \
 		type *a; \
 	} kdq_##type##_t;
 
