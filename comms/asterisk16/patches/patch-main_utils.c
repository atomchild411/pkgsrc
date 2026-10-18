$NetBSD: patch-main_utils.c,v 1.2 2020/03/22 23:09:24 tnn Exp $
IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- main/utils.c.orig
+++ main/utils.c
@@ -41,6 +41,12 @@
 #elif defined(HAVE_SYS_THR_H)
 #include <sys/thr.h>
 #endif
+#if defined(HAVE_GETIFADDRS)
+#include <ifaddrs.h>
+#if !defined(__linux__)
+#include <net/if_dl.h>
+#endif
+#endif
 
 #include "asterisk/network.h"
 #include "asterisk/ast_version.h"
@@ -937,7 +943,7 @@
 
 static int dev_urandom_fd = -1;
 
-#ifndef __linux__
+#if !defined(__linux__) && !defined(__DragonFly__)
 #undef pthread_create /* For ast_pthread_create function only */
 #endif /* !__linux__ */
 
@@ -2817,7 +2823,7 @@
 	return os;
 }
 
-#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__Darwin__)
+#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__Darwin__) || defined(__sgi)
 #include <ifaddrs.h>
 #include <net/if_dl.h>
 
