$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread), 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output) and a667998 (pbuffers start
white and textures made without pixels start clear, not with old graphics memory).

--- src/core.h.orig
+++ src/core.h
@@ -139,6 +139,9 @@
 
 /* Make `c` current in GLX on `d`, if it is not already. */
 int ieg_glx_bind(struct ieg_display *dpy, GLXContext c, GLXDrawable d);
+void ieg_glx_forget(struct ieg_display *dpy);
+void ieg_root_release(struct ieg_display *dpy);
+int ieg_pbuf_take_fresh(GLXDrawable d);
 extern struct ieg_display ieg_the_display;
 
 /* Every GLES entry point starts with IEG_ENTER and leaves with IEG_LEAVE:
