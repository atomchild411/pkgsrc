$NetBSD$

IRIX's getproto*_r are Solaris's (four arguments, returning the result).

--- modules/getent/getent-protocols.c.orig
+++ modules/getent/getent-protocols.c
@@ -28,10 +28,18 @@
   gboolean is_num;
   char buf[4096];
 
+#ifdef __sgi
+  /* IRIX's are Solaris's: four arguments, returning the result. */
+  if ((is_num = parse_int64(key, &d)) == TRUE)
+    res = getprotobynumber_r((int) d, &proto, buf, sizeof(buf));
+  else
+    res = getprotobyname_r(key, &proto, buf, sizeof(buf));
+#else
   if ((is_num = parse_int64(key, &d)) == TRUE)
     getprotobynumber_r((int) d, &proto, buf, sizeof(buf), &res);
   else
     getprotobyname_r(key, &proto, buf, sizeof(buf), &res);
+#endif
 
   if (res == NULL)
     return TRUE;
