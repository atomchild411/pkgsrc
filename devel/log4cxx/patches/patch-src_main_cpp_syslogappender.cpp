$NetBSD$

Where LOG_AUTHPRIV or LOG_FTP is another facility's alias (IRIX: LOG_AUTH, LOG_DAEMON), it is not a case of its own.

--- src/main/cpp/syslogappender.cpp.orig
+++ src/main/cpp/syslogappender.cpp
@@ -142,10 +142,10 @@
         case LOG_NEWS:      return LOG4CXX_STR("news");
         case LOG_UUCP:      return LOG4CXX_STR("uucp");
         case LOG_CRON:      return LOG4CXX_STR("cron");
-#ifdef LOG_AUTHPRIV
+#if defined(LOG_AUTHPRIV) && LOG_AUTHPRIV != LOG_AUTH
         case LOG_AUTHPRIV:  return LOG4CXX_STR("authpriv");
 #endif
-#ifdef LOG_FTP
+#if defined(LOG_FTP) && LOG_FTP != LOG_DAEMON
         case LOG_FTP:       return LOG4CXX_STR("ftp");
 #endif
         case LOG_LOCAL0:    return LOG4CXX_STR("local0");
