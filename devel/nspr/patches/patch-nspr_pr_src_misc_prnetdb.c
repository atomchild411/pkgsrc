$NetBSD$

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/src/misc/prnetdb.c.orig
+++ nspr/pr/src/misc/prnetdb.c
@@ -57,7 +57,7 @@
  * an int, and glibc's flavor takes five arguments.
  */
 
-#if defined(SOLARIS) \
+#if defined(SOLARIS) || defined(IRIX) \
 || (defined(LINUX) && defined(_REENTRANT) && defined(__GLIBC__) && \
     __GLIBC__ < 2)
 #  define _PR_HAVE_GETPROTO_R
