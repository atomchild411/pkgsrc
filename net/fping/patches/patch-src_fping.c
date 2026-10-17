$NetBSD: patch-src_fping.c,v 1.5 2026/01/01 09:24:15 adam Exp $

IP_RECVTOS is not available on NetBSD.
Only ask for IP_RECVTOS and IP_RECVTTL where they exist (not IRIX).

--- src/fping.c.orig
+++ src/fping.c
@@ -712,11 +712,15 @@
                 ping_data_size = ICMP_TIMESTAMP_DATA_SIZE;
             } else if (strstr(optparse_state.optlongname, "print-tos") != NULL) {
                 print_tos_flag = 1;
+#if defined(IP_RECVTOS)
+#ifdef IP_RECVTOS
                 if (socket4 >= 0 && (socktype4 == SOCK_DGRAM)) {
                     if (setsockopt(socket4, IPPROTO_IP, IP_RECVTOS, &sock_opt_on, sizeof(sock_opt_on))) {
                         perror("setsockopt IP_RECVTOS");
                     }
                 }
+#endif
+#endif
 #if defined(IPV6) && defined(IPV6_RECVTCLASS)
                 if (socket6 >= 0) {
                     if (setsockopt(socket6, IPPROTO_IPV6, IPV6_RECVTCLASS, &sock_opt_on, sizeof(sock_opt_on))) {
@@ -726,11 +730,13 @@
 #endif
             } else if (strstr(optparse_state.optlongname, "print-ttl") != NULL) {
                 print_ttl_flag = 1;
+#ifdef IP_RECVTTL
                 if (socket4 >= 0 && (socktype4 == SOCK_DGRAM)) {
                     if (setsockopt(socket4, IPPROTO_IP, IP_RECVTTL, &sock_opt_on, sizeof(sock_opt_on))) {
                         perror("setsockopt IP_RECVTTL");
                     }
                 }
+#endif
 #if defined(IPV6) && defined(IPV6_RECVHOPLIMIT)
                 if (socket6 >= 0) {
                     if (setsockopt(socket6, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, &sock_opt_on, sizeof(sock_opt_on))) {
