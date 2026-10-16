$NetBSD$

IRIX uses utmpx as SGI did: clang defines only __sgi in strict modes.

--- src/include/sysutmp.h.orig
+++ src/include/sysutmp.h
@@ -13,7 +13,7 @@
  *  If we have BOTH utmp.h and utmpx.h, then
  *  we prefer to use utmp.h, but only on systems other than Solaris.
  */
-#if !defined(__sun) && !defined(sgi) && !defined(hpux)
+#if !defined(__sun) && !defined(sgi) && !defined(__sgi) && !defined(hpux)
 #  ifdef HAVE_UTMP_H
 #    undef HAVE_UTMPX_H
 #  endif
