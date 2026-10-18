$NetBSD: patch-misc.c,v 1.1 2017/07/03 11:52:37 wiedi Exp $

no sin_len on SunOS
IRIX: no sin_len either.

--- misc.c.orig
+++ misc.c
@@ -1277,7 +1277,7 @@
   }
   memcpy(&ipaddr.sin_addr.s_addr, hp->h_addr, hp->h_length);
   ipaddr.sin_family = hp->h_addrtype;
-#if !defined(__linux__)
+#if !defined(__linux__) && !defined(__sun) && !defined(__sgi)
   // On BSD, the length is defined in the datastructure
   ipaddr.sin_len = sizeof(struct sockaddr_in);
 #endif // __linux__
