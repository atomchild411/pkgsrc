$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- README.md.orig
+++ README.md
@@ -30,6 +30,14 @@ probe at start, plus each decision; `=2` and `=3` print more (errors,
 pbuffers, drawable switches). With `IRIX_EGL_DEBUG` set, the source of any
 shader program no recipe can draw is saved as `/var/tmp/irix-egl-gles-*.glsl`.
 
+On real SGI graphics, a program must open its display with IRIX's own Xlib
+(`/usr/lib32/libX11.so.1`). When pkgsrc's `libX11.so.6` opens it, SGI's GLX
+makes every context indirect, rendered by a helper process of the X server,
+and the kernel may kill that helper (`RRM_ValidFault` in the system log); the
+program then stops drawing. Loading IRIX's Xlib first fixes it:
+`_RLDN32_LIST=/usr/lib32/libX11.so.1:DEFAULT`. With `IRIX_EGL_DEBUG=1` the
+probe says whether the contexts are direct.
+
 ## How it works
 
 IRIX's OpenGL is 1.1 with SGI extensions: no shaders, no framebuffer
