$NetBSD$

IRIX has no TCP_KEEPIDLE, TCP_KEEPINTVL or TCP_KEEPCNT.

--- res/res_pjsip/config_transport.c.orig
+++ res/res_pjsip/config_transport.c
@@ -843,7 +843,7 @@
 		sockopt_count++;
 
 		if (transport->tcp_keepalive_enable) {
-#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5
+#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5 && defined(TCP_KEEPIDLE)
 			ast_log(LOG_DEBUG, "TCP Keepalive enabled for transport '%s'. Idle Time: %d, Interval: %d, Count: %d\n",
 				ast_sorcery_object_get_id(obj), transport->tcp_keepalive_idle_time, transport->tcp_keepalive_interval_time, transport->tcp_keepalive_probe_count);
 
@@ -910,7 +910,7 @@
 		sockopt_count++;
 
 		if (transport->tcp_keepalive_enable) {
-#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5
+#if defined(PJ_MAX_SOCKOPT_PARAMS) && PJ_MAX_SOCKOPT_PARAMS >= 5 && defined(TCP_KEEPIDLE)
 			ast_log(LOG_DEBUG, "TCP Keepalive enabled for transport '%s'. Idle Time: %d, Interval: %d, Count: %d\n",
 				ast_sorcery_object_get_id(obj), transport->tcp_keepalive_idle_time, transport->tcp_keepalive_interval_time, transport->tcp_keepalive_probe_count);
 
