$NetBSD$

IRIX port (n32, pthreads); NSS dropped its old one.

--- nss/lib/freebl/unix_rand.c.orig
+++ nss/lib/freebl/unix_rand.c
@@ -355,7 +355,7 @@
 
 #endif /* NCR */
 
-#if defined(sgi)
+#if defined(sgi) || defined(__sgi)
 #include <fcntl.h>
 #undef PRIVATE
 #include <sys/mman.h>
@@ -466,6 +466,10 @@
             cntr_size /= 8; /* Convert from bits to bytes */
         }
     }
+    if (iotimer_addr == NULL) {
+        /* no cycle counter */
+        return 0;
+    }
 
     s0[0] = *iotimer_addr;
     if (cntr_size > 4)
