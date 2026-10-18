$NetBSD$

IRIX: getifaddrs EID, endian.h, db1 pgno_t, qlog, RLIMIT_MEMLOCK, TCP keepalive names; GNU sed needs [[:space:]].

--- res/res_pjsip/config_transport.c.orig
+++ res/res_pjsip/config_transport.c
@@ -866,7 +866,7 @@
 		sockopt_count++;
 
 		if (transport->tcp_keepalive_enable) {
-#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5
+#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5 && defined(TCP_KEEPIDLE)
 			ast_log(LOG_DEBUG, "TCP Keepalive enabled for transport '%s'. Idle Time: %d, Interval: %d, Count: %d\n",
 				ast_sorcery_object_get_id(obj), transport->tcp_keepalive_idle_time, transport->tcp_keepalive_interval_time, transport->tcp_keepalive_probe_count);
 
@@ -933,7 +933,7 @@
 		sockopt_count++;
 
 		if (transport->tcp_keepalive_enable) {
-#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5
+#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5 && defined(TCP_KEEPIDLE)
 			ast_log(LOG_DEBUG, "TCP Keepalive enabled for transport '%s'. Idle Time: %d, Interval: %d, Count: %d\n",
 				ast_sorcery_object_get_id(obj), transport->tcp_keepalive_idle_time, transport->tcp_keepalive_interval_time, transport->tcp_keepalive_probe_count);
 
