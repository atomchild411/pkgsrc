$NetBSD$

IRIX has no MAP_ANON: map /dev/zero instead, as the comment says.

--- os/busfault.c.orig
+++ os/busfault.c
@@ -34,6 +34,10 @@
 #include <stdint.h>
 #include <sys/mman.h>
 #include <signal.h>
+#ifndef MAP_ANON
+#include <fcntl.h>
+#include <unistd.h>
+#endif
 
 struct busfault {
     struct xorg_list    list;
@@ -122,9 +126,23 @@
      * /dev/zero over that area and keep going
      */
 
+#ifdef MAP_ANON
     new_addr = mmap(busfault->addr, busfault->size, PROT_READ|PROT_WRITE,
                     MAP_ANON|MAP_PRIVATE|MAP_FIXED, -1, 0);
+#else
+    {
+        int zero = open("/dev/zero", O_RDWR);
 
+        new_addr = MAP_FAILED;
+        if (zero >= 0) {
+            new_addr = mmap(busfault->addr, busfault->size,
+                            PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED,
+                            zero, 0);
+            close(zero);
+        }
+    }
+#endif
+
     if (new_addr == MAP_FAILED)
         goto panic;
 
