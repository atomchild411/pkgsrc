$NetBSD$

IRIX has sig2str() in its libc, which meson finds, but no SIG2STR_MAX:
pulseaudio's own names then.

--- src/pulsecore/core-util.c.orig
+++ src/pulsecore/core-util.c
@@ -1025,7 +1025,7 @@
         goto fail;
 #endif
 
-#ifdef HAVE_SIG2STR
+#if defined(HAVE_SIG2STR) && defined(SIG2STR_MAX)
     {
         char buf[SIG2STR_MAX];
 
