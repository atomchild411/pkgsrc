$NetBSD: patch-nss_lib_freebl_verified_internal_Hacl__Bignum__Base.h,v 1.1 2023/10/04 11:49:22 jperkin Exp $

SunOS needs alloca.h.

IRIX port (n32, pthreads); NSS dropped its old one.

--- nss/lib/freebl/verified/internal/Hacl_Bignum_Base.h.orig
+++ nss/lib/freebl/verified/internal/Hacl_Bignum_Base.h
@@ -30,6 +30,9 @@
 extern "C" {
 #endif
 
+#if defined(__sun) || defined(__sgi)
+#include <alloca.h>
+#endif
 #include <string.h>
 #include "krml/internal/types.h"
 #include "krml/internal/builtin.h"
