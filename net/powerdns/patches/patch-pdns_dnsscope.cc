$NetBSD$

Convert the pcap header's uint32_t seconds to time_t explicitly: a
narrowing conversion where time_t is a 32-bit long (IRIX).

--- pdns/dnsscope.cc.orig
+++ pdns/dnsscope.cc
@@ -130,7 +130,7 @@
 
 static const struct timeval operator-(const struct pdns_timeval& lhs, const struct pdns_timeval& rhs)
 {
-  struct timeval a{lhs.tv_sec, static_cast<suseconds_t>(lhs.tv_usec)}, b{rhs.tv_sec, static_cast<suseconds_t>(rhs.tv_usec)};
+  struct timeval a{static_cast<time_t>(lhs.tv_sec), static_cast<suseconds_t>(lhs.tv_usec)}, b{static_cast<time_t>(rhs.tv_sec), static_cast<suseconds_t>(rhs.tv_usec)};
   return operator-(a,b);
 }
 
