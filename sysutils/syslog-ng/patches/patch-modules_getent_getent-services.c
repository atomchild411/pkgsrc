$NetBSD$

IRIX's getserv*_r are Solaris's (returning the result).

--- modules/getent/getent-services.c.orig
+++ modules/getent/getent-services.c
@@ -28,10 +28,18 @@
   gboolean is_num;
   char buf[4096];
 
+#ifdef __sgi
+  /* IRIX's are Solaris's: no result pointer argument, they return it. */
+  if ((is_num = parse_int64(key, &d)) == TRUE)
+    res = getservbyport_r((int)ntohs(d), NULL, &serv, buf, sizeof(buf));
+  else
+    res = getservbyname_r(key, NULL, &serv, buf, sizeof(buf));
+#else
   if ((is_num = parse_int64(key, &d)) == TRUE)
     getservbyport_r((int)ntohs(d), NULL, &serv, buf, sizeof(buf), &res);
   else
     getservbyname_r(key, NULL, &serv, buf, sizeof(buf), &res);
+#endif
 
   if (res == NULL)
     return TRUE;
