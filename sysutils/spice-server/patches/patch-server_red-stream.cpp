$NetBSD: patch-server_red-stream.cpp,v 1.1 2023/11/09 12:15:50 adam Exp $

TCP_CORK is missing on NetBSD, so disable it (like on win32).
IRIX has neither TCP_CORK nor TCP_NOPUSH: no corking there, as on NetBSD.

--- server/red-stream.cpp.orig
+++ server/red-stream.cpp
@@ -106,7 +106,7 @@
     SpiceCoreInterfaceInternal *core;
 };
 
-#ifndef _WIN32
+#if !defined(_WIN32) && !defined(__NetBSD__) && !defined(__sgi)
 /**
  * Set TCP_CORK on socket
  */
