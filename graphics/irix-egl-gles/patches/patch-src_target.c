$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread), 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output) and a667998 (pbuffers start
white and textures made without pixels start clear, not with old graphics memory).

--- src/target.c.orig
+++ src/target.c
@@ -24,10 +24,55 @@
 #define POOL_MAX 8
 
 void ieg_present_forget(GLXDrawable d);
+
+/* Pbuffers alive and their pixels: on a real board they come out of its
+ * own memory (the screen's and the X server's too). Logged at debug 1. */
+static int live_pbufs;
+static long live_pixels;
+
+/* Pbuffers handed out and not drawn on yet. A pbuffer as it comes from GLX or
+ * the pool holds what was last drawn in that memory: on SGI boards another
+ * frame, often another program's, and WebKit, drawing only what it counts as
+ * damaged, may never cover all of it. So the first time a context is bound to
+ * one (ieg_glx_bind, on the binding thread: GLX refuses a context current on
+ * another thread), it is cleared to white. */
+#define FRESH_MAX 64
+static GLXDrawable fresh[FRESH_MAX];
+
+static void
+fresh_drop(GLXDrawable d)
+{
+    int i;
+
+    for (i = 0; i < FRESH_MAX; i++)
+        if (fresh[i] == d)
+            fresh[i] = None;
+}
+
+/* Whether d is a pbuffer not drawn on yet; it no longer is after this. */
+int
+ieg_pbuf_take_fresh(GLXDrawable d)
+{
+    int i;
+
+    if (d == None)
+        return 0;
+    for (i = 0; i < FRESH_MAX; i++)
+        if (fresh[i] == d) {
+            fresh[i] = None;
+            return 1;
+        }
+    return 0;
+}
 
 static void
 pbuf_destroy(struct ieg_display *dpy, struct ieg_pbuf *pb)
 {
+    fresh_drop(pb->id);
+    live_pbufs--;
+    live_pixels -= (long)pb->w * pb->h;
+    ieg_dbg(1, "pbuffer -%#lx %dx%d: live %d (%ld kpx), pool %d", (unsigned long)pb->id, pb->w, pb->h,
+        live_pbufs, live_pixels / 1000, dpy->npool);
     ieg_present_forget(pb->id);
     /* Not while anything is current on it. */
     ieg_glx_bind(dpy, dpy->root, dpy->null_pb->id);
@@ -35,10 +80,29 @@
         ieg_self()->ctx->drawable = None;
     G.glXDestroyGLXPbufferSGIX(dpy->x, pb->id);
     free(pb);
+    ieg_root_release(dpy);
 }
 
+static struct ieg_pbuf *pbuf_get(struct ieg_display *dpy, int w, int h);
+
 struct ieg_pbuf *
 ieg_pbuf_get(struct ieg_display *dpy, int w, int h)
+{
+    struct ieg_pbuf *pb = pbuf_get(dpy, w, h);
+    int i;
+
+    if (pb != NULL) {
+        fresh_drop(pb->id);
+        for (i = 0; i < FRESH_MAX && fresh[i] != None; i++)
+            ;
+        if (i < FRESH_MAX)
+            fresh[i] = pb->id;
+    }
+    return pb;
+}
+
+static struct ieg_pbuf *
+pbuf_get(struct ieg_display *dpy, int w, int h)
 {
     struct ieg_pbuf **pp, *pb;
     GLXPbufferSGIX id;
@@ -66,6 +130,7 @@
         id = ieg_make_pbuffer(dpy, w, h);
     }
     if (id == None) {
+        ieg_dbg(1, "pbuffer %dx%d FAILED: live %d (%ld kpx), pool %d", w, h, live_pbufs, live_pixels / 1000, dpy->npool);
         ieg_once("pbuffer-fail", "cannot create a %dx%d pbuffer (out of pbuffer memory?)", w, h);
         return NULL;
     }
@@ -73,7 +138,10 @@
     pb->id = id;
     pb->w = w;
     pb->h = h;
-    ieg_dbg(2, "pbuffer %#lx %dx%d", (unsigned long)id, w, h);
+    live_pbufs++;
+    live_pixels += (long)w * h;
+    ieg_dbg(1, "pbuffer +%#lx %dx%d: live %d (%ld kpx), pool %d", (unsigned long)id, w, h, live_pbufs,
+        live_pixels / 1000, dpy->npool);
     return pb;
 }
 
