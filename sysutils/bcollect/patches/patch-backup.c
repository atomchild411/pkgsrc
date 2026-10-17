$NetBSD$

flock() and LOCK_EX are in <sys/file.h> (IRIX).

--- backup.c.orig
+++ backup.c
@@ -30,6 +30,7 @@
  */
 
 #include <bcollect.h>
+#include <sys/file.h>
 
 #ifndef MIN
 #define MIN(a,b)	((a) < (b) ? (a) : (b))
