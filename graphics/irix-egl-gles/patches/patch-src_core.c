$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/core.c.orig
+++ src/core.c
@@ -10,6 +10,7 @@
  */
 #include <stdio.h>
 #include <stdlib.h>
+#include <unistd.h>
 #include <string.h>
 #include <stdarg.h>
 #include <dlfcn.h>
@@ -112,6 +113,19 @@ ieg_glx_forget(struct ieg_display *dpy)
     }
 }
 
+/* The root context, made current on this thread for a moment (a pbuffer or
+ * a context going, objects freed, an expose repaint), let go of again. Every
+ * thread uses it so, and GLX refuses a context current on another thread
+ * (BadAccess): left current here, it would be refused everywhere else. */
+void
+ieg_root_release(struct ieg_display *dpy)
+{
+    if (!dpy->caps.glx_current_per_thread || ieg_self()->glx_ctx != dpy->root)
+        return;
+    G.glXMakeCurrent(dpy->x, None, NULL);
+    ieg_glx_forget(dpy);
+}
+
 void
 ieg_use(struct ieg_ctx *ctx)
 {
@@ -156,6 +170,8 @@ ieg_dbg(int level, const char *fmt, ...)
 
     if (ieg_debug < level)
         return;
+    /* which thread: contexts and drawables are bound per thread */
+    fprintf(stderr, "[%lx pid %d] ", (unsigned long)pthread_self(), (int)getpid());
     va_start(ap, fmt);
     vlog(fmt, ap);
     va_end(ap);
