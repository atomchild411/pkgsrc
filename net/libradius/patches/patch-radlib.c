$NetBSD: patch-radlib.c,v 1.1 2014/02/24 12:43:11 wiedi Exp $

'struct sockaddr_in' has no member named 'sin_len' on SunOS
IRIX: no sin_len either.

--- radlib.c.orig
+++ radlib.c
@@ -250,7 +250,7 @@
 	srvp = &h->servers[h->num_servers];
 
 	memset(&srvp->addr, 0, sizeof srvp->addr);
-#if !defined(__linux__)
+#if !defined(__linux__) && !defined(__sun) && !defined(__sgi)
         srvp->addr.sin_len = sizeof srvp->addr;
 #endif
 	srvp->addr.sin_family = AF_INET;
@@ -617,7 +617,7 @@
 			return -1;
 		}
 		memset(&sin, 0, sizeof sin);
-#if !defined(__linux__)
+#if !defined(__linux__) && !defined(__sun) && !defined(__sgi)
 		sin.sin_len = sizeof sin;
 #endif
 		sin.sin_family = AF_INET;
