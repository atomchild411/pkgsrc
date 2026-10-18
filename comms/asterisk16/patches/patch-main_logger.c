$NetBSD$

IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- main/logger.c.orig
+++ main/logger.c
@@ -197,6 +197,9 @@
 static ast_cond_t logcond;
 static int close_logger_thread = 0;
 
+#ifdef qlog	/* IRIX <math.h>: qlog is logl */
+#undef qlog
+#endif
 static FILE *qlog;
 
 /*! \brief Logging channels used in the Asterisk logging system
