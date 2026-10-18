$NetBSD$

IRIX <sys/types.h> defines cnt_t and index_t.

--- include/bignum.h.orig
+++ include/bignum.h
@@ -60,6 +60,9 @@
 #define	RSASIZE_MIN (RSABITS/3/LIMBBITS)
 #define	RSASIZE_MAX (RSABITS/2/LIMBBITS)
 
+/* IRIX's <sys/types.h> has a cnt_t (short): rename this one. */
+#include <sys/types.h>
+#define cnt_t bn_cnt_t
 typedef uint32_t cnt_t;
 typedef uint16_t half_t;
 typedef uint32_t limb_t;
