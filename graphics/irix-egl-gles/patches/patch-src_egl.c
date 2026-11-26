$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/egl.c.orig
+++ src/egl.c
@@ -11,6 +11,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <dlfcn.h>
 #include <EGL/egl.h>
 #include <EGL/eglext.h>
 #include "state.h"
@@ -603,6 +604,11 @@ ieg_eglCreateContext(EGLDisplay d, EGLConfig cfg, EGLContext share_context, cons
     ctx->dpy = dpy;
     ctx->config = c;
     ctx->glx = G.glXCreateContextWithConfigSGIX(dpy->x, c->fb, GLX_RGBA_TYPE_SGIX, dpy->root, True);
+    if (ieg_debug >= 1 && ctx->glx != NULL) { /* direct, or rendered by the X server? */
+        Bool (*is_direct)(Display *, GLXContext) = (Bool (*)(Display *, GLXContext))dlsym(dpy->libgl, "glXIsDirect");
+        ieg_dbg(1, "context %p: config %d, %s", (void *)ctx->glx, c->id,
+            is_direct ? (is_direct(dpy->x, ctx->glx) ? "direct" : "INDIRECT") : "direct?");
+    }
     if (ctx->glx == NULL) {
         free(ctx);
         ieg_unlock();
@@ -645,6 +651,7 @@ context_free(struct ieg_ctx *ctx)
     G.glXDestroyContext(dpy->x, ctx->glx);
     free(ctx->extensions);
     free(ctx);
+    ieg_root_release(dpy);
 }
 
 EGLBoolean
