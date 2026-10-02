$NetBSD$

IRIX snoop: pcapint_filter() takes the program length too.

--- pcap-snoop.c.orig	2026-10-02 13:51:08.680351250 +0000
+++ pcap-snoop.c	2026-10-02 13:51:08.680351250 +0000
@@ -124,7 +124,8 @@
 	}
 
 	if (p->fcode.bf_insns == NULL ||
-	    pcapint_filter(p->fcode.bf_insns, cp, datalen, caplen)) {
+	    pcapint_filter(p->fcode.bf_insns, p->fcode.bf_len, cp,
+	    datalen, caplen)) {
 		struct pcap_pkthdr h;
 		++psn->stat.ps_recv;
 		h.ts.tv_sec = sh->snoop_timestamp.tv_sec;
