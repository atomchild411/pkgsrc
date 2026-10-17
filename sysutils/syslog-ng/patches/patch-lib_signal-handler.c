$NetBSD$

IRIX: no RTLD_NEXT; call libc's _sigaction.

--- lib/signal-handler.c.orig
+++ lib/signal-handler.c
@@ -86,6 +86,10 @@
 {
 #ifdef __NetBSD__
   return __libc_sigaction14(signum, act, oldact);
+#elif defined(__sgi)
+  /* IRIX's rld has no RTLD_NEXT; libc's sigaction is _sigaction. */
+  extern int _sigaction(int, const struct sigaction *, struct sigaction *);
+  return _sigaction(signum, act, oldact);
 #else
   static int (*real_sa)(int, const struct sigaction *, struct sigaction *);
 
