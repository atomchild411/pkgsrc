$NetBSD$

IRIX: <xti.h> defines a T_DATA of its own, which ruby's headers refuse;
IRIX's <netinet/tcp.h> has the TCP options ruby wants from it.

--- ext/socket/rubysocket.h.orig	2026-10-02 15:15:19.513639715 +0000
+++ ext/socket/rubysocket.h	2026-10-02 15:15:19.513639715 +0000
@@ -28,7 +28,7 @@
 #  include <sys/uio.h>
 #endif
 
-#ifdef HAVE_XTI_H
+#if defined(HAVE_XTI_H) && !defined(__sgi)
 #  include <xti.h>
 #endif
 
