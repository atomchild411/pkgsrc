$NetBSD$

An empty #elif: #else was meant (platforms without a memory query).

--- osdep.c.orig
+++ osdep.c
@@ -268,7 +268,7 @@
   // There is some way to get memory information on switch (see include switch/kernel/svc.h svcGetInfo svcGetSystemInfo)
   // but the usage is a bit confusing for the first and the later need privilege to be used.
   // If you come here with a solution, you'r welcome. For now we just return the default value.
-#elif
+#else
 #warning "There is missing code there for your platform ! please check and correct :)"
 #endif
   return 10*1024*1024;
