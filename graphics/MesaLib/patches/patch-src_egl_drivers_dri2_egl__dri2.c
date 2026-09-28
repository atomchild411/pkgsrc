$NetBSD$

IRIX condition variables only take CLOCK_REALTIME deadlines.

--- src/egl/drivers/dri2/egl_dri2.c.orig
+++ src/egl/drivers/dri2/egl_dri2.c
@@ -3417,8 +3417,13 @@
          return NULL;
       }
 
+#ifndef __sgi
       /* change clock attribute to CLOCK_MONOTONIC */
       ret = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
+#else
+      /* IRIX condition variables only take CLOCK_REALTIME deadlines. */
+      ret = 0;
+#endif
 
       if (ret) {
          _eglError(EGL_BAD_ACCESS, "eglCreateSyncKHR");
@@ -3579,7 +3584,11 @@
 
             /* We override the clock to monotonic when creating the condition
              * variable. */
+#ifndef __sgi
             clock_gettime(CLOCK_MONOTONIC, &current);
+#else
+            clock_gettime(CLOCK_REALTIME, &current);
+#endif
 
             /* calculating when to expire */
             expire.tv_nsec = timeout % 1000000000L;
