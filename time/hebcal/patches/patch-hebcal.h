$NetBSD$

IRIX: <sys/time.h> defines the BSD timezone constant DST_NONE as a macro, which turned this enum constant into a number.

--- hebcal.h.orig
+++ hebcal.h
@@ -78,6 +78,7 @@
    int leap_p;
 } year_t;
 
+#undef DST_NONE	/* IRIX <sys/time.h>: the BSD timezone constant */
 enum dst_type {
     DST_USOFA = 0,
     DST_NONE = 1,
