$NetBSD: patch-nxcomp_src_Socket.cpp,v 1.1 2021/02/24 18:38:43 hauke Exp $

Add NetBSD conditional where we find FreeBSD's.
IRIX: SOL_IP is IPPROTO_IP there too.

--- nxcomp/src/Socket.cpp.orig
+++ nxcomp/src/Socket.cpp
@@ -30,7 +30,7 @@
 #include <sys/types.h>
 #include <sys/utsname.h>
 
-#if defined(__CYGWIN32__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__sun)
+#if defined(__CYGWIN32__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__sun)
 #include <netinet/in_systm.h>
 #endif
 
@@ -51,7 +51,7 @@
 // System specific defines.
 //
 
-#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__sun)
+#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__sun) || defined(__sgi)
 #define SOL_IP  IPPROTO_IP
 #endif
 
