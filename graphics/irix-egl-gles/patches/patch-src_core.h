$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/core.h.orig
+++ src/core.h
@@ -139,6 +139,8 @@ struct ieg_thread *ieg_self(void);
 
 /* Make `c` current in GLX on `d`, if it is not already. */
 int ieg_glx_bind(struct ieg_display *dpy, GLXContext c, GLXDrawable d);
+void ieg_glx_forget(struct ieg_display *dpy);
+void ieg_root_release(struct ieg_display *dpy);
 extern struct ieg_display ieg_the_display;
 
 /* Every GLES entry point starts with IEG_ENTER and leaves with IEG_LEAVE:
