$NetBSD$

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/src/misc/prsystem.c.orig
+++ nspr/pr/src/misc/prsystem.c
@@ -233,7 +233,7 @@
 PR_IMPLEMENT(PRUint64) PR_GetPhysicalMemorySize(void) {
   PRUint64 bytes = 0;
 
-#if defined(LINUX) || defined(SOLARIS)
+#if defined(LINUX) || defined(SOLARIS) || defined(IRIX)
 
   long pageSize = sysconf(_SC_PAGESIZE);
   long pageCount = sysconf(_SC_PHYS_PAGES);
