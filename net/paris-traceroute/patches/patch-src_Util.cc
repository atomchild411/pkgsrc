$NetBSD: patch-src_Util.cc,v 1.2 2020/03/27 20:52:19 joerg Exp $

SunOS needs strings.h for bzero().
IRIX: bzero is in <strings.h>.

--- src/Util.cc.orig
+++ src/Util.cc
@@ -5,6 +5,10 @@
 
 #include <stdio.h>
 #include <string.h>
+#include <strings.h>
+#ifdef __sun
+#include <strings.h>
+#endif
 #include <unistd.h>
 //#include <asm/types.h>
 #include <sys/ioctl.h>
@@ -89,7 +93,7 @@
   fscanf(fd, "%s", buff);
   pclose(fd);
 
-  log(INFO, "Source address = %s\n", buff);
+  mylog(INFO, "Source address = %s\n", buff);
 
   return strdup(buff);
 }
@@ -243,7 +247,7 @@
 int
 Util::protocol2int (const char* protocol) {
   struct protoent* proto = getprotobyname(protocol);
-  log(DUMP, "p_proto = %d", proto->p_proto);
+  mylog(DUMP, "p_proto = %d", proto->p_proto);
   return proto->p_proto;
 }
 
@@ -278,12 +282,12 @@
    struct hostent* phost = gethostbyname(host);
    if (phost == NULL || phost->h_addrtype != AF_INET) {
      // Not a valid IP4 address
-     log(ERROR, "Invalid address");
+     mylog(ERROR, "Invalid address");
      return NULL;
    }
    struct in_addr *buff = (in_addr*)phost->h_addr_list[0];
    char* dst_addr = strdup(inet_ntoa(*buff));
-   log(DUMP, "dst_addr = %s", dst_addr);
+   mylog(DUMP, "dst_addr = %s", dst_addr);
    return dst_addr;
  }
 }
