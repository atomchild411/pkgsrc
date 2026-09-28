$NetBSD$

Build without libdrm (IRIX): its only use is the DMA-BUF import probe.

--- src/gallium/frontends/dri/dri2.c.orig
+++ src/gallium/frontends/dri/dri2.c
@@ -28,7 +28,9 @@
  *    <wallbraker@gmail.com> Chia-I Wu <olv@lunarg.com>
  */
 
+#ifdef HAVE_LIBDRM
 #include <xf86drm.h>
+#endif
 #include "GL/mesa_glinterop.h"
 #include "util/disk_cache.h"
 #include "util/u_memory.h"
@@ -2275,6 +2277,7 @@
          dri2_create_image_with_modifiers2;
    }
 
+#ifdef HAVE_LIBDRM
    if (pscreen->get_param(pscreen, PIPE_CAP_DMABUF)) {
       uint64_t cap;
 
@@ -2294,6 +2297,7 @@
          }
       }
    }
+#endif
    *nExt++ = &screen->image_extension.base;
 
    if (!is_kms_screen) {
