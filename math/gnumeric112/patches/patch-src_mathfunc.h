$NetBSD$

IRIX <math.h> also maps qexp to expl, as qgamma (handled above).

--- src/mathfunc.h.orig
+++ src/mathfunc.h
@@ -14,6 +14,10 @@
 #warning "Your <math.h> is somewhat broken; we'll work around that."
 #undef qgamma
 #endif
+#ifdef qexp
+/* IRIX: qexp is expl. */
+#undef qexp
+#endif
 
 #define M_PIgnum    GNM_const(3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117)
 #define M_PI_2gnum (M_PIgnum / 2)
