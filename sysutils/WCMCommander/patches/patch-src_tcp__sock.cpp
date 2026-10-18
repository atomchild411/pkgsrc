$NetBSD: patch-src_tcp__sock.cpp,v 1.2 2015/09/08 13:21:46 wiz Exp $

NetBSD does not have gethostbyname_r() either.
https://github.com/corporateshark/WCMCommander/pull/509
IRIX's takes five arguments (Solaris style), not glibc's six.

--- src/tcp_sock.cpp.orig
+++ src/tcp_sock.cpp
@@ -64,7 +64,7 @@
 
 	struct hostent* ret;
 
-#if defined( __APPLE__ ) || defined(__OpenBSD__)
+#if defined( __APPLE__ ) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__sgi)
 	ret = gethostbyname( utf8 );
 
 	if ( !ret )
