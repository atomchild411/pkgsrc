$NetBSD$

IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- include/asterisk/endian.h.orig
+++ include/asterisk/endian.h
@@ -29,7 +29,7 @@
 
 
 #ifndef __BYTE_ORDER
-#ifdef __linux__
+#if defined(__linux__) || defined(__sgi)
 #include <endian.h>
 #elif defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__APPLE__)
 #if defined(__OpenBSD__)
