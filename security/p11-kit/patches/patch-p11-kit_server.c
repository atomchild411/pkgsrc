$NetBSD$

IRIX's __sighandler_t is the union inside its struct sigaction, not a
handler type: use the fallback typedef there.

--- p11-kit/server.c.orig
+++ p11-kit/server.c
@@ -73,7 +73,8 @@
 #define SIGHANDLER_T sighandler_t
 #elif HAVE_SIG_T
 #define SIGHANDLER_T sig_t
-#elif HAVE___SIGHANDLER_T
+#elif HAVE___SIGHANDLER_T && !defined(__sgi)
+/* IRIX has a __sighandler_t too, but it is a union, not a handler. */
 #define SIGHANDLER_T __sighandler_t
 #else
 typedef void (*sighandler_t)(int);
