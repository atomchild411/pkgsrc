$NetBSD: patch-src_TCPProbe.cc,v 1.1 2020/03/27 20:52:19 joerg Exp $
With using namespace std, bind() can resolve to std::bind; call ::bind().

--- src/TCPProbe.cc.orig
+++ src/TCPProbe.cc
@@ -104,7 +104,7 @@
   buff.sin_family       = AF_INET;
   buff.sin_port         = htons(tcp->getSourcePort());
   buff.sin_addr.s_addr  = ip4->getSourceAddress();
-  res = bind(sock, (sockaddr*)&buff, sizeof(sockaddr_in));
+  res = ::bind(sock, (sockaddr*)&buff, sizeof(sockaddr_in));
   if (res < 0) throw TrException(str_log(ERROR,
                 "Can't bind to source address : %s", strerror(errno)));
 
@@ -132,10 +132,10 @@
 
 void
 TCPProbe::dump () {
-  log(DUMP, "==> TCP Probe :");
+  mylog(DUMP, "==> TCP Probe :");
   for (int i = 0; i  < getNbrHeaders(); i++)
     getHeader(i)->dump();
-  log(DUMP, "Data :");
+  mylog(DUMP, "Data :");
   if (data != NULL)
     dumpRawData(DUMP, data, data_length);
 }
@@ -145,7 +145,7 @@
   uint8* data;
   int   length;
   getDatagram(&data, &length);
-  log(DUMP, "==> TCP Probe :");
+  mylog(DUMP, "==> TCP Probe :");
   dumpRawData(DUMP, data, length);
 }
 
