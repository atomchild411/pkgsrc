$NetBSD$

IRIX: no way to list the routing table (no netlink, no routing sysctl): not supported, as on older Android.

--- src/enum_net.cpp.orig
+++ src/enum_net.cpp
@@ -1483,7 +1483,7 @@
 				i = reinterpret_cast<ifreq const*>(reinterpret_cast<char const*>(i) + skip);
 			}
 		}
-#elif defined TORRENT_ANDROID && __ANDROID_API__ >= 24
+#elif (defined TORRENT_ANDROID && __ANDROID_API__ >= 24) || defined __sgi
 		ec = boost::asio::error::operation_not_supported;
 #else
 #error "don't know how to enumerate network routes on this platform"
