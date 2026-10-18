$NetBSD$

IRIX's sockaddr has no sa_len in the X/Open mode Poco builds in.

--- Net/include/Poco/Net/SocketDefs.h.orig
+++ Net/include/Poco/Net/SocketDefs.h
@@ -243,7 +243,7 @@
 #endif
 
 
-#if defined(POCO_OS_FAMILY_BSD) || (POCO_OS == POCO_OS_TRU64) || (POCO_OS == POCO_OS_AIX) || (POCO_OS == POCO_OS_IRIX) || (POCO_OS == POCO_OS_QNX) || (POCO_OS == POCO_OS_VXWORKS)
+#if defined(POCO_OS_FAMILY_BSD) || (POCO_OS == POCO_OS_TRU64) || (POCO_OS == POCO_OS_AIX) || (POCO_OS == POCO_OS_QNX) || (POCO_OS == POCO_OS_VXWORKS)
 	#define POCO_HAVE_SALEN 1
 #endif
 
