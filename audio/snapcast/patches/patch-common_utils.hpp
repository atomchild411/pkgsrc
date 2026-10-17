$NetBSD: patch-common_utils.hpp,v 1.2 2025/09/30 06:49:37 adam Exp $

Add NetBSD support.
IRIX has no SIOCGIFHWADDR (nor AF_LINK addresses): no MAC address there, which the caller copes with.

--- common/utils.hpp.orig
+++ common/utils.hpp
@@ -38,7 +38,7 @@
 #include <string>
 #include <sys/stat.h>
 #include <sys/types.h>
-#if !defined(WINDOWS) && !defined(FREEBSD)
+#if !defined(WINDOWS) && !defined(FREEBSD) && !defined(__NetBSD__)
 #include <sys/sysinfo.h>
 #endif
 #ifdef MACOS
@@ -47,6 +47,10 @@
 #include <ifaddrs.h>
 #include <net/if_dl.h>
 #endif
+#ifdef __NetBSD__
+#include <ifaddrs.h>
+#include <net/if_dl.h>
+#endif
 #ifdef ANDROID
 #include <sys/system_properties.h>
 #endif
@@ -304,7 +308,7 @@
         {
             if (!(ifr.ifr_flags & IFF_LOOPBACK)) // don't count loopback
             {
-#ifdef MACOS
+#if defined(MACOS) || defined(__NetBSD__)
                 /// Dirty Mac version
                 struct ifaddrs *ifap, *ifaptr;
                 unsigned char* ptr;
@@ -331,6 +335,7 @@
                 }
 #endif
 
+#if !defined(__NetBSD__) && !defined(__sgi)
 #ifdef FREEBSD
                 if (ioctl(sock, SIOCGIFMAC, &ifr) == 0)
 #else
@@ -353,6 +358,7 @@
                             return line;
                     }
                 }
+#endif
             }
         }
         else
@@ -367,7 +373,7 @@
         return "";
 
     char mac[19];
-#ifndef FREEBSD
+#if !defined(FREEBSD) && !defined(__NetBSD__) && !defined(__sgi)
     sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", (unsigned char)ifr.ifr_hwaddr.sa_data[0], (unsigned char)ifr.ifr_hwaddr.sa_data[1],
             (unsigned char)ifr.ifr_hwaddr.sa_data[2], (unsigned char)ifr.ifr_hwaddr.sa_data[3], (unsigned char)ifr.ifr_hwaddr.sa_data[4],
             (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
