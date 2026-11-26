$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/present.c.orig
+++ src/present.c
@@ -24,12 +24,12 @@
 #include "state.h"
 #include "gen/api.h"
 
-void ieg_glx_forget(struct ieg_display *dpy);
 
 struct present {
     Window parent, child;
     int w, h;               /* child size = last frame size */
     int flip;
+    int whole;              /* made or resized: the next frame goes in whole */
     GLXDrawable src;        /* where the last frame is; None if gone */
     struct present *next;
 };
@@ -45,7 +45,11 @@ x_error(Display *d, XErrorEvent *e)
     char text[128];
 
     XGetErrorText(d, e->error_code, text, sizeof text);
-    ieg_once("x-error", "X error: %s (request %d); carrying on", text, e->request_code);
+    if (ieg_debug >= 1)
+        ieg_dbg(1, "X error: %s (request %d.%d, resource %#lx, serial %lu)", text, e->request_code,
+            e->minor_code, (unsigned long)e->resourceid, (unsigned long)e->serial);
+    else
+        ieg_once("x-error", "X error: %s (request %d); carrying on", text, e->request_code);
     return 0;
 }
 
@@ -66,6 +70,8 @@ copy(struct ieg_display *dpy, GLXContext ctx, struct present *p, const int *rect
     GLfloat ortho[16] = { 0 };
     int i, whole[4];
 
+    ieg_dbg(3, "present: glXMakeCurrentReadSGI(window %#lx, pbuffer %#lx, %p)", (unsigned long)p->child,
+        (unsigned long)p->src, (void *)ctx);
     if (!G.glXMakeCurrentReadSGI(dpy->x, p->child, p->src, ctx)) {
         ieg_once("present-current", "cannot read a pbuffer while drawing to a window here");
         ieg_glx_forget(dpy);
@@ -136,6 +142,8 @@ watch(void *arg)
     struct ieg_display *dpy = arg;
     XEvent ev;
 
+    ieg_dbg(1, "expose watcher started");
+
     for (;;) {
         struct present *p;
         int r[4];
@@ -150,6 +158,11 @@ watch(void *arg)
         for (p = presents; p != NULL; p = p->next)
             if (p->child == ev.xexpose.window && p->src != None)
                 copy(dpy, dpy->root, p, r, 1);
+        /* not current here between exposes: the root context is every thread's */
+        if (G.glXGetCurrentContext() == dpy->root) {
+            G.glXMakeCurrent(dpy->x, None, NULL);
+            ieg_glx_forget(dpy);
+        }
         ieg_unlock();
     }
     return NULL;
@@ -179,12 +192,16 @@ find(struct ieg_display *dpy, Window parent, int w, int h, int flip)
         swa.colormap = XCreateColormap(dpy->x, RootWindow(dpy->x, dpy->screen), vi->visual, AllocNone);
         swa.border_pixel = 0;
         swa.background_pixmap = None;
+        /* A resize keeps what is shown (X's default throws it away: black
+         * until the next frame, and a frame of damaged rects leaves it so). */
+        swa.bit_gravity = NorthWestGravity;
         p->child = XCreateWindow(dpy->x, parent, 0, 0, w, h, 0, vi->depth, InputOutput, vi->visual,
-            CWColormap | CWBorderPixel | CWBackPixmap, &swa);
+            CWColormap | CWBorderPixel | CWBackPixmap | CWBitGravity, &swa);
         XMapWindow(dpy->x, p->child);
         XSync(dpy->x, False);
         p->w = w;
         p->h = h;
+        p->whole = 1;
         p->next = presents;
         presents = p;
         if (watch_x != NULL) {
@@ -199,6 +216,7 @@ find(struct ieg_display *dpy, Window parent, int w, int h, int flip)
         XResizeWindow(dpy->x, p->child, w, h);
         p->w = w;
         p->h = h;
+        p->whole = 1;
     }
     p->flip = flip;
     return p;
@@ -225,7 +243,11 @@ ieg_eglPresentToWindowIRIX(EGLDisplay d, EGLNativeWindowType parent, EGLint widt
         return EGL_FALSE;
     }
     p->src = ctx->drawable;
-    copy(dpy, ctx->glx, p, rects, n_rects > 0 && rects != NULL ? n_rects : 0);
+    /* A window just made or resized may hold nothing of the last frame (a
+     * real server discards contents on resize when it must): the rects say
+     * what changed since that frame, so the whole of this one goes in. */
+    copy(dpy, ctx->glx, p, rects, n_rects > 0 && rects != NULL && !p->whole ? n_rects : 0);
+    p->whole = 0;
     ieg_use(ctx);
     ieg_unlock();
     return EGL_TRUE;
