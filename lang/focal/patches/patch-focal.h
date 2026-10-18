$NetBSD$

IRIX <math.h> defines fsin, fcos, fexp and flog.

--- focal.h.orig
+++ focal.h
@@ -13,6 +13,13 @@
 #include <setjmp.h>
 #include <signal.h>
 #include <math.h>
+#ifdef __sgi
+/* IRIX's <math.h> defines these as its float functions (sinf, ...). */
+#undef fsin
+#undef fcos
+#undef fexp
+#undef flog
+#endif
 
 #define	FUNCTIONS			/* enable functions */
 #define	NID	16			/* # characters in id */
