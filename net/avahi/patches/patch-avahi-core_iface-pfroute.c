$NetBSD$

IRIX: routing-message sockaddrs carry a length byte and a family byte; its struct sockaddr has neither.

--- avahi-core/iface-pfroute.c.orig
+++ avahi-core/iface-pfroute.c
@@ -46,6 +46,20 @@
 #include "iface-pfroute.h"
 #include "util.h"
 
+#ifdef __sgi
+/* IRIX's struct sockaddr has a 16-bit family and no length, but its
+   routing messages carry 4.4BSD sockaddrs: a length byte (possibly 0),
+   then a family byte (its <sys/socket.h> struct sockaddr_new and
+   _FAKE_SA_LEN_DST). */
+#define PFR_SA_FAMILY(sa) (((const unsigned char *)(sa))[1])
+#define PFR_SA_LEN(sa) (((const unsigned char *)(sa))[0] ?		\
+			((const unsigned char *)(sa))[0] :		\
+			PFR_SA_FAMILY(sa) == AF_LINK ? 20 : sizeof(struct sockaddr))
+#else
+#define PFR_SA_FAMILY(sa) ((sa)->sa_family)
+#define PFR_SA_LEN(sa) ((sa)->sa_len)
+#endif
+
 #ifdef __NetBSD__
 #define lifreq if_laddrreq
 #define lifr_addr iflr_addr
@@ -118,7 +132,7 @@
 #define ROUNDUP(a) \
      ((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
 #ifdef HAVE_SYS_SYSCTL_H
-#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))
+#define ADVANCE(x, n) (x += ROUNDUP(PFR_SA_LEN(n)))
 #else
 #define ADVANCE(x, n) (x += ROUNDUP(sizeof(struct sockaddr)))
 #endif
@@ -138,6 +152,10 @@
 #if defined(__NetBSD__) || defined(__OpenBSD__)
   if(((struct sockaddr *)cp)->sa_family == AF_UNSPEC)
     ((struct sockaddr *)cp)->sa_family = AF_INET;
+#elif defined(__sgi)
+  /* IRIX too gives the netmask no family; set the family byte. */
+  if(PFR_SA_FAMILY(cp) == AF_UNSPEC)
+    ((unsigned char *)cp)[1] = AF_INET;
 #endif
 
   for (cp0 = cp, i = 0; i < RTAX_MAX; i++) {
@@ -153,13 +171,13 @@
 #endif
   }
 
-  if(sa->sa_family != AF_INET && sa->sa_family != AF_INET6)
+  if(PFR_SA_FAMILY(sa) != AF_INET && PFR_SA_FAMILY(sa) != AF_INET6)
     return;
 
-  if (!(iface = avahi_interface_monitor_get_interface(m, (AvahiIfIndex) ifam->ifam_index, avahi_af_to_proto(sa->sa_family))))
+  if (!(iface = avahi_interface_monitor_get_interface(m, (AvahiIfIndex) ifam->ifam_index, avahi_af_to_proto(PFR_SA_FAMILY(sa)))))
     return;
 
-  raddr.proto = avahi_af_to_proto(sa->sa_family);
+  raddr.proto = avahi_af_to_proto(PFR_SA_FAMILY(sa));
 
   for(cp = cp0, i = 0; i < RTAX_MAX; i++)
     {
@@ -167,10 +185,10 @@
 	continue;
       sa = (struct sockaddr *)cp;
 #ifdef HAVE_SYS_SYSCTL_H
-      if (sa->sa_len == 0)
+      if (PFR_SA_LEN(sa) == 0)
 	continue;
 #endif
-      switch(sa->sa_family) {
+      switch(PFR_SA_FAMILY(sa)) {
       case AF_INET:
 	switch (1<<i) {
 	case RTA_NETMASK:
