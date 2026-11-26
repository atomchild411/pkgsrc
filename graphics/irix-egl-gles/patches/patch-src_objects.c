$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/objects.c.orig
+++ src/objects.c
@@ -132,6 +132,7 @@ ieg_share_unref(struct ieg_display *dpy, struct ieg_share *s)
     table_free(&s->renderbuffers);
     table_free(&s->glsl);
     free(s);
+    ieg_root_release(dpy);
 }
 
 struct ieg_texture *
