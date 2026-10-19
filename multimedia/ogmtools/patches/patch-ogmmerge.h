$NetBSD$

IRIX <sys/types.h> has a stamp_t: rename this one.

--- ogmmerge.h.orig
+++ ogmmerge.h
@@ -39,6 +39,8 @@
   double end;
 } range_t;
 
+#include <sys/types.h>
+#define stamp_t ogm_stamp_t
 typedef double stamp_t;
 #define MAX_TIMESTAMP ((double)3.40282347e+38F)
 
