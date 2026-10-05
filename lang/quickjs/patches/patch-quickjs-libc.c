$NetBSD: patch-quickjs-libc.c,v 1.3 2022/01/30 10:55:03 he Exp $

Portability patch for NetBSD.
IRIX has no sighandler_t either.

--- quickjs-libc.c.orig	2026-06-04 12:26:08.000000000 +0000
+++ quickjs-libc.c
@@ -811,6 +811,8 @@
     return JS_UNDEFINED;
 }
 
+extern char **environ; /* Needed at least for NetBSD-8.0-x86_64. */
+
 /* return an object containing the list of the available environment
    variables. */
 static JSValue js_std_getenviron(JSContext *ctx, JSValueConst this_val,
@@ -2077,7 +2079,7 @@
     os_pending_signals |= ((uint64_t)1 << sig_num);
 }
 
-#if defined(_WIN32)
+#if defined(_WIN32) || defined(__NetBSD__) || defined(__sgi)
 typedef void (*sighandler_t)(int sig_num);
 #endif
 
