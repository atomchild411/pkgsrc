$NetBSD: patch-main_utils.c,v 1.1 2024/04/08 03:20:09 jnemeth Exp $
IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- main/utils.c.orig
+++ main/utils.c
@@ -41,7 +41,11 @@
 #elif defined(__NetBSD__)
 #include <lwp.h>
 #endif
-
+#if defined(HAVE_GETIFADDRS)
+#include <ifaddrs.h>
+#include <net/if_dl.h>
+#endif
+ 
 #include "asterisk/network.h"
 #include "asterisk/ast_version.h"
 
@@ -213,7 +217,7 @@
 	while (s && *s) {
 		if (*s == '.')
 			dots++;
-		else if (!isdigit(*s))
+		else if (!isdigit((unsigned char)*s))
 			break;
 		s++;
 	}
@@ -973,7 +977,7 @@
 
 static int dev_urandom_fd = -1;
 
-#ifndef __linux__
+#if !defined(__linux__) && !defined(__DragonFly__)
 #undef pthread_create /* For ast_pthread_create function only */
 #endif /* !__linux__ */
 
@@ -2274,13 +2278,13 @@
 static struct timeval tvfix(struct timeval a)
 {
 	if (a.tv_usec >= ONE_MILLION) {
-		ast_log(LOG_WARNING, "warning too large timestamp %ld.%ld\n",
-			(long)a.tv_sec, (long int) a.tv_usec);
+		ast_log(LOG_WARNING, "warning too large timestamp %jd.%ld\n",
+			(intmax_t)a.tv_sec, (long int) a.tv_usec);
 		a.tv_sec += a.tv_usec / ONE_MILLION;
 		a.tv_usec %= ONE_MILLION;
 	} else if (a.tv_usec < 0) {
-		ast_log(LOG_WARNING, "warning negative timestamp %ld.%ld\n",
-			(long)a.tv_sec, (long int) a.tv_usec);
+		ast_log(LOG_WARNING, "warning negative timestamp %jd.%ld\n",
+			(intmax_t)a.tv_sec, (long int) a.tv_usec);
 		a.tv_usec = 0;
 	}
 	return a;
@@ -2440,7 +2444,7 @@
 
 	while (front) {
 		size = strlen(front);
-		*front = toupper(*front);
+		*front = toupper((unsigned char)*front);
 		ast_copy_string(buf, front, size + 1);
 		buf += size;
 		front = strtok_r(NULL, delim, &back);
@@ -2890,7 +2894,7 @@
 	return os;
 }
 
-#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__Darwin__)
+#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__Darwin__) || defined(__sgi)
 #include <ifaddrs.h>
 #include <net/if_dl.h>
 
