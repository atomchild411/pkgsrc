$NetBSD$

IRIX: no d_type, ALLPERMS or TCP keepalive names.

--- res/res_http_websocket.c.orig
+++ res/res_http_websocket.c
@@ -2027,9 +2027,11 @@
 		int enabled = 1;
 
 		setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &enabled, sizeof(enabled));
+#ifdef TCP_KEEPIDLE	/* not on IRIX */
 		setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE, &options->tcp_keepalive_time, sizeof(options->tcp_keepalive_time));
 		setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL, &options->tcp_keepalive_interval, sizeof(&options->tcp_keepalive_interval));
 		setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPCNT, &options->tcp_keepalive_probes, sizeof(&options->tcp_keepalive_probes));
+#endif
 		ast_trace(-1, "%s: Enabled TCP keepalives\n", ws->client->options->uri);
 	}
 
