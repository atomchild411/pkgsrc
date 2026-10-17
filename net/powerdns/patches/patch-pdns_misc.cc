$NetBSD$

Only the syslog facilities the system has (IRIX: no LOG_AUTHPRIV or LOG_FTP).
setDscp: getsockopt takes a socklen_t, which is not unsigned int everywhere.

--- pdns/misc.cc.orig
+++ pdns/misc.cc
@@ -669,10 +669,14 @@
     {"log_uucp", LOG_UUCP},
     {"cron", LOG_CRON},
     {"log_cron", LOG_CRON},
+#ifdef LOG_AUTHPRIV
     {"authpriv", LOG_AUTHPRIV},
     {"log_authpriv", LOG_AUTHPRIV},
+#endif
+#ifdef LOG_FTP
     {"ftp", LOG_FTP},
-    {"log_ftp", LOG_FTP}
+    {"log_ftp", LOG_FTP},
+#endif
   };
 
   toLowerInPlace(facilityStr);
@@ -999,7 +1003,7 @@
 void setDscp(int sock, unsigned short family, uint8_t dscp)
 {
   int val = 0;
-  unsigned int len = 0;
+  socklen_t len = 0;
 
   if (dscp == 0 || dscp > 63) {
     // No DSCP marking
