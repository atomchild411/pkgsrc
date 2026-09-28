$NetBSD$

IRIX: no IPv6 (6.5.7 declares struct sockaddr_in6 only under INET6, and
we build without IPv6); leave out the AF_INET6 cases.

--- src/xcb_auth.c.orig
+++ src/xcb_auth.c
@@ -122,7 +122,7 @@
     family = FamilyLocal; /* 256 */
     switch(sockname->sa_family)
     {
-#ifdef AF_INET6
+#if defined(AF_INET6) && !defined(__sgi)
     case AF_INET6:
         addr = (char *) SIN6_ADDR(sockname);
         addrlen = sizeof(*SIN6_ADDR(sockname));
@@ -213,7 +213,7 @@
             APPEND(info->data, j, si->sin_port);
         }
         break;
-#ifdef AF_INET6
+#if defined(AF_INET6) && !defined(__sgi)
         case AF_INET6:
             /*block*/ {
             struct sockaddr_in6 *si6 = (struct sockaddr_in6 *) sockname;
