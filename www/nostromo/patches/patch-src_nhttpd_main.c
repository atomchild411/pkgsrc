$NetBSD$

IRIX has no sin6_len.

--- src/nhttpd/main.c.orig
+++ src/nhttpd/main.c
@@ -1002,7 +1002,7 @@
 				err(1, "setsockopt");
 
 			/* bind */
-			#ifndef __linux__
+			#if !defined(__linux__) && !defined(__sgi)
 			sa6.sin6_len = sizeof(sa6);
 			#endif
 			sa6.sin6_family = AF_INET6;
@@ -1077,7 +1077,7 @@
 				err(1, "setsockopt");
 
 			/* bind */
-			#ifndef __linux__
+			#if !defined(__linux__) && !defined(__sgi)
 			sa6.sin6_len = sizeof(sa6);
 			#endif
 			sa6.sin6_family = AF_INET6;
