$NetBSD$

getsockopt() takes a socklen_t (int on IRIX), initialized to the buffer size.

--- misc.cc.orig
+++ misc.cc
@@ -1000,7 +1000,7 @@
 void setDscp(int sock, unsigned short family, uint8_t dscp)
 {
   int val = 0;
-  unsigned int len = 0;
+  socklen_t len = sizeof(val);
 
   if (dscp == 0 || dscp > 63) {
     // No DSCP marking
