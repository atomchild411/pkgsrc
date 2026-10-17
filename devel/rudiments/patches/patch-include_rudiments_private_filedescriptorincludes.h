$NetBSD$

IRIX with clang: no _XOPEN_SOURCE around <sys/socket.h>. Whether it takes
effect depends on include order, so socklen_t (int or size_t) differed
between files and librudiments referenced a getSockOpt it did not define.

--- include/rudiments/private/filedescriptorincludes.h.orig
+++ include/rudiments/private/filedescriptorincludes.h
@@ -16,7 +16,9 @@
 #ifdef RUDIMENTS_HAVE_SYS_SOCKET_H
 	// IRIX appears to need this but OpenBSD can't
 	// find select() if it's still defined later
-	#ifndef _XOPEN_SOURCE
+	// (Not with clang's IRIX headers: whether it takes effect depends on
+	// what came first, so socklen_t differed between files.)
+	#if !defined(_XOPEN_SOURCE) && !(defined(__sgi) && defined(__clang__))
 		#define _XOPEN_SOURCE
 		#define UN_XOPEN_SOURCE
 	#endif
