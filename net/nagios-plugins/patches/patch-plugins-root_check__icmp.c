$NetBSD$

chdr exists only with SO_TIMESTAMP, which IRIX lacks: without it the time is always taken with gettimeofday.

--- plugins-root/check_icmp.c.orig
+++ plugins-root/check_icmp.c
@@ -1329,7 +1329,10 @@
   }
 #endif /* SO_TIMESTAMP */
 
-  if (!chdr) {
+#ifdef SO_TIMESTAMP
+  if (!chdr)
+#endif
+  {
     gettimeofday(tv, &tz);
   }
   return (ret);
