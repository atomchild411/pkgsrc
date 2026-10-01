$NetBSD$

Apply MacPorts patch-libuv-legacy.diff for pre-10.7 platforms.

IRIX has no source-specific multicast.

--- src/unix/udp.c.orig
+++ src/unix/udp.c
@@ -843,7 +843,9 @@ static int uv__udp_set_membership6(uv_udp_t* handle,
     !defined(__ANDROID__) &&                                        \
     !defined(__DragonFly__) &&                                      \
     !defined(__GNU__) &&                                            \
-    !defined(QNX_IOPKT)
+    !defined(__sgi) &&                                             \
+    !defined(QNX_IOPKT) && \
+    (!defined(__APPLE__) || MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
 static int uv__udp_set_source_membership4(uv_udp_t* handle,
                                           const struct sockaddr_in* multicast_addr,
                                           const char* interface_addr,
@@ -1055,7 +1057,9 @@ int uv_udp_set_source_membership(uv_udp_t* handle,
     !defined(__ANDROID__) &&                                        \
     !defined(__DragonFly__) &&                                      \
     !defined(__GNU__) &&                                          \
-    !defined(QNX_IOPKT)
+    !defined(__sgi) &&                                             \
+    !defined(QNX_IOPKT) && \
+    (!defined(__APPLE__) || MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
   int err;
   union uv__sockaddr mcast_addr;
   union uv__sockaddr src_addr;
