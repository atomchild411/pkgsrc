$NetBSD$

Without libdrm (IRIX) there are no DRM devices: go straight to swrast.

--- src/egl/drivers/dri2/platform_surfaceless.c.orig
+++ src/egl/drivers/dri2/platform_surfaceless.c
@@ -26,7 +26,9 @@
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
+#ifdef HAVE_LIBDRM
 #include <xf86drm.h>
+#endif
 #include <dlfcn.h>
 #include <sys/types.h>
 #include <sys/stat.h>
@@ -225,6 +227,10 @@
 static bool
 surfaceless_probe_device(_EGLDisplay *disp, bool swrast)
 {
+#ifndef HAVE_LIBDRM
+   /* No DRM devices without libdrm. */
+   return false;
+#else
 #define MAX_DRM_DEVICES 64
    const unsigned node_type = swrast ? DRM_NODE_PRIMARY : DRM_NODE_RENDER;
    struct dri2_egl_display *dri2_dpy = dri2_egl_display(disp);
@@ -288,6 +294,7 @@
       dri2_dpy->loader_extensions = image_loader_extensions;
 
    return true;
+#endif
 }
 
 static bool
@@ -331,7 +338,12 @@
     * is true, we try kms_swrast and swrast in order.
     */
    driver_loaded = surfaceless_probe_device(disp, disp->Options.ForceSoftware);
+#ifdef HAVE_LIBDRM
    if (!driver_loaded && disp->Options.ForceSoftware) {
+#else
+   /* Without libdrm there is only software rendering. */
+   if (!driver_loaded) {
+#endif
       _eglLog(_EGL_DEBUG, "Falling back to surfaceless swrast without DRM.");
       driver_loaded = surfaceless_probe_device_sw(disp);
    }
