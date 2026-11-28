$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread), 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output) and a667998 (pbuffers start
white and textures made without pixels start clear, not with old graphics memory).

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
@@ -96,6 +97,19 @@
     ieg_dbg(3, "glXMakeCurrent(%#lx, %p)", (unsigned long)d, (void *)c);
     *pc = c;
     *pd = d;
+    if (ieg_pbuf_take_fresh(d)) {
+        /* A pbuffer's first use: white, like WebKit's own page background, so what WebKit has not
+         * drawn yet (a page still loading, a tab's tiles being repainted after it was hidden) shows
+         * as an empty page, not as what the memory held. WebKit clears a layer's target itself
+         * before drawing into it, so layers are unaffected. */
+        G.glPushAttrib(GL_COLOR_BUFFER_BIT | GL_SCISSOR_BIT);
+        G.glDisable(GL_SCISSOR_TEST);
+        G.glColorMask(1, 1, 1, 1);
+        G.glClearColor(1, 1, 1, 1);
+        G.glClear(GL_COLOR_BUFFER_BIT);
+        G.glPopAttrib();
+        ieg_dbg(1, "pbuffer %#lx cleared to white before its first use", (unsigned long)d);
+    }
     return 1;
 }
 
@@ -112,7 +126,20 @@
     }
 }
 
+/* The root context, made current on this thread for a moment (a pbuffer or
+ * a context going, objects freed, an expose repaint), let go of again. Every
+ * thread uses it so, and GLX refuses a context current on another thread
+ * (BadAccess): left current here, it would be refused everywhere else. */
 void
+ieg_root_release(struct ieg_display *dpy)
+{
+    if (!dpy->caps.glx_current_per_thread || ieg_self()->glx_ctx != dpy->root)
+        return;
+    G.glXMakeCurrent(dpy->x, None, NULL);
+    ieg_glx_forget(dpy);
+}
+
+void
 ieg_use(struct ieg_ctx *ctx)
 {
     GLXDrawable d = ctx->drawable != None ? ctx->drawable : ieg_default_drawable(ctx);
@@ -156,6 +183,8 @@
 
     if (ieg_debug < level)
         return;
+    /* which thread: contexts and drawables are bound per thread */
+    fprintf(stderr, "[%lx pid %d] ", (unsigned long)pthread_self(), (int)getpid());
     va_start(ap, fmt);
     vlog(fmt, ap);
     va_end(ap);
