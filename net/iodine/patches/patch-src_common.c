$NetBSD$

IRIX: daemon() is declared (and provided by the toolchain).

--- src/common.c.orig
+++ src/common.c
@@ -57,7 +57,7 @@
 const unsigned char raw_header[RAW_HDR_LEN] = { 0x10, 0xd1, 0x9e, 0x00 };
 
 /* daemon(3) exists only in 4.4BSD or later, and in GNU libc */
-#if !defined(ANDROID) && !defined(WINDOWS32) && !(defined(BSD) && (BSD >= 199306)) && !defined(__GLIBC__)
+#if !defined(ANDROID) && !defined(WINDOWS32) && !(defined(BSD) && (BSD >= 199306)) && !defined(__GLIBC__) && !defined(__sgi)
 static int daemon(int nochdir, int noclose)
 {
  	int fd, i;
