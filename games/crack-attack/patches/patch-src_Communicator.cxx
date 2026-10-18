$NetBSD$

accept() takes a socklen_t (int on IRIX).

--- src/Communicator.cxx.orig
+++ src/Communicator.cxx
@@ -158,7 +158,7 @@
 #endif
 
 #ifndef _WIN32
-    unsigned int length = sizeof(address);
+    socklen_t length = sizeof(address);
 #else
     int length = sizeof(address);
 #endif
