$NetBSD$

clang does not support the FENV_ACCESS pragma on MIPS.

--- jttb/jttb.c.orig
+++ jttb/jttb.c
@@ -41,7 +41,9 @@
 
 #ifndef __vax__
 #include <fenv.h>
+#if !(defined(__clang__) && defined(__mips__))	/* not supported there */
 #pragma STDC FENV_ACCESS ON
+#endif
 #endif /* __vax__ */
 
 #include "../tbvm/tbvm.h"
