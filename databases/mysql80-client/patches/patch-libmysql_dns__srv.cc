$NetBSD$

IRIX: DNS SRV through res_search, without libresolv.

--- libmysql/dns_srv.cc.orig
+++ libmysql/dns_srv.cc
@@ -38,6 +38,59 @@
 #include <netdb.h>
 #include <resolv.h>
 
+#ifdef __sgi
+#include <arpa/nameser.h>
+
+// IRIX version: its resolver (BIND 4) has res_search and dn_expand but
+// no res_n* or ns_* parsing functions, so walk the answer by hand.
+
+static bool get_dns_srv(Dns_srv_data &data, const char *dnsname, int &error) {
+  unsigned char buf[PACKETSZ * 4];
+  char name[MAXDNAME];
+
+  data.clear();
+  int len = res_search(dnsname, C_IN, T_SRV, buf, sizeof(buf));
+  if (len < HFIXEDSZ) {
+    error = h_errno;
+    return true;
+  }
+  if (len > (int)sizeof(buf)) len = sizeof(buf);
+  const unsigned char *end = buf + len;
+  const unsigned char *p = buf + HFIXEDSZ;
+  const HEADER *hp = (const HEADER *)buf;
+  int qd = ntohs(hp->qdcount), an = ntohs(hp->ancount);
+
+  while (qd-- > 0) {
+    int n = dn_skipname(p, end);
+    if (n < 0 || p + n + QFIXEDSZ > end) return false;
+    p += n + QFIXEDSZ;
+  }
+  while (an-- > 0) {
+    int n = dn_expand(buf, end, p, name, sizeof(name));
+    if (n < 0 || p + n + RRFIXEDSZ > end) break;
+    p += n;
+    unsigned short type, cls, rdlen;
+    GETSHORT(type, p);
+    GETSHORT(cls, p);
+    p += 4;  // TTL
+    GETSHORT(rdlen, p);
+    if (p + rdlen > end) break;
+    if (type == T_SRV && cls == C_IN && rdlen > 6) {
+      const unsigned char *q = p;
+      unsigned short prio, weight, port;
+      GETSHORT(prio, q);
+      GETSHORT(weight, q);
+      GETSHORT(port, q);
+      if (dn_expand(buf, end, q, name, sizeof(name)) >= 0)
+        data.add(name, port, prio, weight);
+    }
+    p += rdlen;
+  }
+  return false;
+}
+
+#else
+
 // POSIX version
 
 static bool get_dns_srv(Dns_srv_data &data, const char *dnsname, int &error) {
@@ -100,6 +153,7 @@
 #endif
   return ret;
 }
+#endif /* __sgi */
 
 #elif defined(HAVE_WIN32_DNS_SRV)
 #include <windns.h>
