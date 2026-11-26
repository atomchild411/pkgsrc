$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/target.c.orig
+++ src/target.c
@@ -25,9 +25,18 @@ GLXPbufferSGIX ieg_make_pbuffer(struct ieg_display *dpy, int w, int h);
 
 void ieg_present_forget(GLXDrawable d);
 
+/* Pbuffers alive and their pixels: on a real board they come out of its
+ * own memory (the screen's and the X server's too). Logged at debug 1. */
+static int live_pbufs;
+static long live_pixels;
+
 static void
 pbuf_destroy(struct ieg_display *dpy, struct ieg_pbuf *pb)
 {
+    live_pbufs--;
+    live_pixels -= (long)pb->w * pb->h;
+    ieg_dbg(1, "pbuffer -%#lx %dx%d: live %d (%ld kpx), pool %d", (unsigned long)pb->id, pb->w, pb->h,
+        live_pbufs, live_pixels / 1000, dpy->npool);
     ieg_present_forget(pb->id);
     /* Not while anything is current on it. */
     ieg_glx_bind(dpy, dpy->root, dpy->null_pb->id);
@@ -35,6 +44,7 @@ pbuf_destroy(struct ieg_display *dpy, struct ieg_pbuf *pb)
         ieg_self()->ctx->drawable = None;
     G.glXDestroyGLXPbufferSGIX(dpy->x, pb->id);
     free(pb);
+    ieg_root_release(dpy);
 }
 
 struct ieg_pbuf *
@@ -66,6 +76,7 @@ ieg_pbuf_get(struct ieg_display *dpy, int w, int h)
         id = ieg_make_pbuffer(dpy, w, h);
     }
     if (id == None) {
+        ieg_dbg(1, "pbuffer %dx%d FAILED: live %d (%ld kpx), pool %d", w, h, live_pbufs, live_pixels / 1000, dpy->npool);
         ieg_once("pbuffer-fail", "cannot create a %dx%d pbuffer (out of pbuffer memory?)", w, h);
         return NULL;
     }
@@ -73,7 +84,10 @@ ieg_pbuf_get(struct ieg_display *dpy, int w, int h)
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
 
