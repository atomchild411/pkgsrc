$NetBSD$

An xlib surface whose visual has no XRender format (xrender_format NULL) was
still drawn with the XRender compositor and used as a native XRender source,
so XRenderCreatePicture() got a NULL format and crashed (snes9x-gtk on IRIX).
Draw such surfaces with the core X11 compositor, as on servers without
RENDER, and upload them as images when they are used as a source.

--- src/cairo-xlib-source.c.orig
+++ src/cairo-xlib-source.c
@@ -1141,6 +1141,7 @@
 	if (pattern->type == CAIRO_PATTERN_TYPE_SURFACE) {
 	    cairo_surface_pattern_t *spattern = (cairo_surface_pattern_t *)pattern;
 	    if (spattern->surface->type == CAIRO_SURFACE_TYPE_XLIB &&
+		unwrap_source (spattern)->xrender_format != NULL &&
 		_cairo_xlib_surface_same_screen (dst,
 						 unwrap_source (spattern)))
 		return native_source (dst, spattern, is_mask,
