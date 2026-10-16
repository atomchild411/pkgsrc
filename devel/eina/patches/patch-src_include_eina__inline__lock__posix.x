$NetBSD$

struct timespec is <time.h>'s (IRIX's <sys/time.h> does not bring it).

--- src/include/eina_inline_lock_posix.x.orig
+++ src/include/eina_inline_lock_posix.x
@@ -40,6 +40,7 @@
 #include <semaphore.h>
 
 #include <sys/time.h>
+#include <time.h>
 #include <stdio.h>
 
 #ifdef EINA_HAVE_DEBUG_THREADS
