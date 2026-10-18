$NetBSD: patch-main_logger.c,v 1.1 2024/04/08 03:20:09 jnemeth Exp $
IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- main/logger.c.orig
+++ main/logger.c
@@ -195,6 +195,9 @@
 static ast_cond_t logcond;
 static int close_logger_thread = 0;
 
+#ifdef qlog	/* IRIX <math.h>: qlog is logl */
+#undef qlog
+#endif
 static FILE *qlog;
 
 /*! \brief Logging channels used in the Asterisk logging system
@@ -1027,7 +1030,7 @@
 
 	if (qlog) {
 		va_start(ap, fmt);
-		qlog_len = snprintf(qlog_msg, sizeof(qlog_msg), "%ld|%s|%s|%s|%s|", (long)time(NULL), callid, queuename, agent, event);
+		qlog_len = snprintf(qlog_msg, sizeof(qlog_msg), "%jd|%s|%s|%s|%s|", (intmax_t)time(NULL), callid, queuename, agent, event);
 		vsnprintf(qlog_msg + qlog_len, sizeof(qlog_msg) - qlog_len, fmt, ap);
 		va_end(ap);
 		AST_RWLIST_RDLOCK(&logchannels);
@@ -1067,7 +1070,7 @@
 		}
 		break;
 	case TIMESTAMP:
-		snprintf(new, sizeof(new), "%s.%ld", filename, (long)time(NULL));
+		snprintf(new, sizeof(new), "%s.%jd", filename, (intmax_t)time(NULL));
 		if (rename(filename, new)) {
 			fprintf(stderr, "Unable to rename file '%s' to '%s'\n", filename, new);
 			res = -1;
