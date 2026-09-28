$NetBSD$

IRIX: alloca is in <alloca.h>.

--- include/c99_alloca.h.orig
+++ include/c99_alloca.h
@@ -35,7 +35,7 @@
 
 #  define alloca _alloca
 
-#elif defined(__sun) || defined(__CYGWIN__)
+#elif defined(__sun) || defined(__CYGWIN__) || defined(__sgi)
 
 #  include <alloca.h>
 
