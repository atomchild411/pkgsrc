$NetBSD: patch-agent_mibgroup_mibII_ip.c,v 1.1 2022/10/18 12:01:52 adam Exp $

IRIX: the reassembly timeout is the kernel's IPFRAGTTL (slow timeout ticks):
there is no ip-mib arch implementation to ask.

--- agent/mibgroup/mibII/ip.c.orig
+++ agent/mibgroup/mibII/ip.c
@@ -26,6 +26,10 @@
 #include "ip.h"
 #include "ipAddr.h"
 #include "interfaces.h"
+#ifdef __sgi
+#include <netinet/ip.h>		/* IPFRAGTTL */
+#include <sys/protosw.h>	/* PR_SLOWHZ */
+#endif
 
 #ifndef MIB_STATS_CACHE_TIMEOUT
 #define MIB_STATS_CACHE_TIMEOUT	5
@@ -260,6 +264,18 @@
 #define	USES_TRADITIONAL_IPSTAT
 #endif
 
+#ifdef IP_NSTATS
+typedef struct ipstat {
+	uint64_t st[IP_NSTATS];
+};
+#define IP_STAT_STRUCTURE	struct ipstat
+#endif
+
+#ifdef dragonfly
+#define IP_STAT_STRUCTURE	struct ip_stats
+#define	USES_TRADITIONAL_IPSTAT
+#endif
+
 #if !defined(IP_STAT_STRUCTURE)
 #define IP_STAT_STRUCTURE	struct ipstat
 #define	USES_TRADITIONAL_IPSTAT
@@ -463,7 +479,11 @@
         netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
         continue;
     case IPREASMTIMEOUT:
+#if defined(__sgi) && defined(IPFRAGTTL) && defined(PR_SLOWHZ)
+        ret_value = IPFRAGTTL / PR_SLOWHZ;
+#else
         ret_value = netsnmp_arch_ip_scalars_ipReasmTimeout_get();
+#endif
         type = ASN_INTEGER;
         break;
     case IPREASMREQDS:
