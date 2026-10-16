$NetBSD: patch-src_main_listen.c,v 1.3 2024/07/24 14:28:05 manu Exp $

Fix missing SOL_TCP for other platforms.
IRIX: SOL_TCP is IPPROTO_TCP.

--- src/main/listen.c.orig
+++ src/main/listen.c
@@ -59,7 +59,7 @@
 #ifdef WITH_TLS
 #include <netinet/tcp.h>
 
-#  if defined(__APPLE__) || defined(__FreeBSD__) || defined(__illumos__) || defined(__sun__)
+#  if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__illumos__) || defined(__sun__) || defined(__sgi)
 #    if !defined(SOL_TCP) && defined(IPPROTO_TCP)
 #      define SOL_TCP IPPROTO_TCP
 #    endif
