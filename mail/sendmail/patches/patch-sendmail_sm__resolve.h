$NetBSD$

Resolvers without EDNS0 or DNSSEC flags (IRIX's): define them as 0, as
RES_TRUSTAD already is.

--- sendmail/sm_resolve.h.orig
+++ sendmail/sm_resolve.h
@@ -171,6 +171,13 @@
 #ifndef RES_TRUSTAD
 # define RES_TRUSTAD	0
 #endif
+/* Resolvers without EDNS0 or DNSSEC (IRIX's): no such flags. */
+#ifndef RES_USE_EDNS0
+# define RES_USE_EDNS0	0
+#endif
+#ifndef RES_USE_DNSSEC
+# define RES_USE_DNSSEC	0
+#endif
 #define SM_RES_DNSSEC (RES_USE_EDNS0|RES_USE_DNSSEC|RES_TRUSTAD)
 
 #endif /* DNSMAP || DANE */
