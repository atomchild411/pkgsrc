$NetBSD$

IRIX: XPG5 mode (siginfo_t, IOV_MAX), and the XPG timezone variable (its struct timezone is BSD/SGI-only).

--- src/fmacros.h.orig
+++ src/fmacros.h
@@ -27,6 +27,8 @@
  * On NetBSD, _XOPEN_SOURCE undefines _NETBSD_SOURCE and
  * thus hides inet_aton etc.
  */
+#elif defined(__sgi)
+#define _XOPEN_SOURCE 600
 #elif !defined(__NetBSD__)
 #define _XOPEN_SOURCE
 #endif
