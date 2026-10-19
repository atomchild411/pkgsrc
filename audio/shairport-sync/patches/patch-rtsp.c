$NetBSD$

IRIX has no TCP_KEEPIDLE.

--- rtsp.c.orig
+++ rtsp.c
@@ -5642,10 +5642,12 @@
 #define KEEP_ALIVE_OR_IDLE_OPTION TCP_KEEPIDLE
 #endif
 
+#if defined(COMPILE_FOR_OSX) || defined(TCP_KEEPIDLE)
             if (setsockopt(conn->fd, SOL_OPTION, KEEP_ALIVE_OR_IDLE_OPTION,
                            (void *)&keepAliveIdleTime, sizeof(keepAliveIdleTime))) {
               debug(1, "can't set the keepAliveIdleTime wait time");
             }
+#endif
 // ---
 // if TCP_KEEPINTVL is defined...
 #ifdef TCP_KEEPINTVL
