$NetBSD$

An xlib surface whose visual has no XRender format (xrender_format NULL) was
still drawn with the XRender compositor and used as a native XRender source,
so XRenderCreatePicture() got a NULL format and crashed (snes9x-gtk on IRIX).
Draw such surfaces with the core X11 compositor, as on servers without
RENDER, and upload them as images when they are used as a source.

--- src/cairo-xlib-surface.c.orig
+++ src/cairo-xlib-surface.c
@@ -1806,6 +1806,8 @@
 
     surface->screen = screen;
     surface->compositor = display->compositor;
+    if (xrender_format == NULL)
+	surface->compositor = _cairo_xlib_core_compositor_get ();
     surface->shm = NULL;
     surface->fallback = 0;
 
