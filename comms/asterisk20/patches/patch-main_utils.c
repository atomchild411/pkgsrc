$NetBSD: patch-main_utils.c,v 1.2 2024/10/26 13:12:23 ryoon Exp $
IRIX: the default EID from getifaddrs, as on the BSDs (no SIOCGIFHWADDR).

--- main/utils.c.orig
+++ main/utils.c
@@ -937,7 +937,7 @@
 
 static int dev_urandom_fd = -1;
 
-#ifndef __linux__
+#if !defined(__linux__) && !defined(__DragonFly__)
 #undef pthread_create /* For ast_pthread_create function only */
 #endif /* !__linux__ */
 
@@ -2854,7 +2854,7 @@
 	return os;
 }
 
-#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__Darwin__)
+#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__Darwin__) || defined(__sgi)
 #include <ifaddrs.h>
 #include <net/if_dl.h>
 
