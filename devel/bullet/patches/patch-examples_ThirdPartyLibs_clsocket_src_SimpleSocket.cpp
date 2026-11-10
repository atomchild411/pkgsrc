$NetBSD$

IRIX: recvfrom's address length is an int *.

--- examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp.orig
+++ examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp
@@ -756,7 +756,11 @@
 		}
 		case CSimpleSocket::SocketTypeUdp:
 		{
+#if defined(__sgi)
+			int srcSize;  // IRIX: recvfrom's address length is an int *
+#else
 			uint32 srcSize;
+#endif
 
 			srcSize = sizeof(struct sockaddr_in);
 
