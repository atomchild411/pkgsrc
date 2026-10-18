$NetBSD$

Pass the addresses as struct sockaddr *: where bind() and connect() take a const void * (IRIX), the conversion from Socket::address is ambiguous.

--- commoncpp/udp.cpp.orig
+++ commoncpp/udp.cpp
@@ -217,7 +217,7 @@
     int opt = 1;
     setsockopt(so, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, (socklen_t)sizeof(opt));
 #endif
-    if(bind(so, peer, (socklen_t)peer.getLength())) {
+    if(bind(so, (struct sockaddr *)peer, (socklen_t)peer.getLength())) {
         endSocket();
         error(errBindingFailed,(char *)"Could not bind socket",socket_errno);
         return;
@@ -232,7 +232,7 @@
     int opt = 1;
     setsockopt(so, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, (socklen_t)sizeof(opt));
 #endif
-    if(bind(so, peer, sizeof(sockaddr_in))) {
+    if(bind(so, (struct sockaddr *)peer, sizeof(sockaddr_in))) {
         endSocket();
         error(errBindingFailed,(char *)"Could not bind socket",socket_errno);
         return;
@@ -248,7 +248,7 @@
     int opt = 1;
     setsockopt(so, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, (socklen_t)sizeof(opt));
 #endif
-    if(bind(so, peer, sizeof(sockaddr_in6))) {
+    if(bind(so, (struct sockaddr *)peer, sizeof(sockaddr_in6))) {
         endSocket();
         error(errBindingFailed,(char *)"Could not bind socket",socket_errno);
         return;
@@ -449,7 +449,7 @@
     if(so == INVALID_SOCKET)
         return;
 
-    rtn = ::connect(so, peer, (socklen_t)peer.getLength());
+    rtn = ::connect(so, (struct sockaddr *)peer, (socklen_t)peer.getLength());
     if(!rtn)
         Socket::state = CONNECTED;
 }
@@ -543,7 +543,7 @@
     peer = host;
     if(peer.isAny())
         peer.setLoopback();
-    if(::connect(so, peer, (socklen_t)peer.getLength()))
+    if(::connect(so, (struct sockaddr *)peer, (socklen_t)peer.getLength()))
         return connectError();
     return errSuccess;
 }
@@ -629,7 +629,7 @@
     if(host.isAny())
         host.setLoopback();
 
-    if(::connect(so, host, (socklen_t)host.getLength()))
+    if(::connect(so, (struct sockaddr *)host, (socklen_t)host.getLength()))
         return connectError();
     return errSuccess;
 }
