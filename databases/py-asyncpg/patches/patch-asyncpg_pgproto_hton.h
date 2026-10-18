$NetBSD$

IRIX: <endian.h> (clang's IRIX wrappers).

--- asyncpg/pgproto/hton.h.orig
+++ asyncpg/pgproto/hton.h
@@ -1,6 +1,6 @@
 #include <stdint.h>
 
-#if defined(__linux__) || defined(__CYGWIN__) || defined(__sun)
+#if defined(__linux__) || defined(__CYGWIN__) || defined(__sun) || defined(__sgi)
 #include <endian.h>
 #elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__OpenBSD__) \
       || defined(__DragonFly__)
