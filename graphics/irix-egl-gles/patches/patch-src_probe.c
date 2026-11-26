$NetBSD$

From the author's repository, commits 1287c30 (release the root GL context after
each use, on every thread) and 861467a (window-capable GLX configs first, whole
frames after a create or resize, more debug output).

--- src/probe.c.orig
+++ src/probe.c
@@ -8,6 +8,7 @@
  */
 #include <stdio.h>
 #include <stdlib.h>
+#include <dlfcn.h>
 #include <string.h>
 #include <sys/time.h>
 #include "state.h"
@@ -89,6 +90,28 @@ choose_configs(struct ieg_display *dpy)
         c->id = ++k;
     }
     dpy->nconfigs = k;
+    /* Configurations a window can have first, numbered again: the root
+     * configuration (contexts share its lists; present_to_window's window
+     * gets its visual) must have a visual, and an application's choice
+     * should match it. GLX lists pbuffer-only ones first on some boards
+     * (VPro: 8-bit alpha and stencil without a visual before 0x41/0x43),
+     * and with no visual frames could only be read back. */
+    {
+        int w = 0, j;
+        for (i = 0; i < k; i++)
+            if (dpy->configs[i].vi != NULL) {
+                struct ieg_config t = dpy->configs[i];
+                for (j = i; j > w; j--)
+                    dpy->configs[j] = dpy->configs[j - 1];
+                dpy->configs[w++] = t;
+            }
+        for (i = 0; i < k; i++)
+            dpy->configs[i].id = i + 1;
+        for (i = 0; i < k; i++)
+            ieg_dbg(1, "config %d: visual %#lx, depth %d, stencil %d, %s", dpy->configs[i].id,
+                dpy->configs[i].vi ? (unsigned long)dpy->configs[i].vi->visualid : 0UL, dpy->configs[i].depth,
+                dpy->configs[i].stencil, dpy->configs[i].doublebuffer ? "double" : "single");
+    }
     dpy->root_config = k > 0 ? &dpy->configs[0] : NULL;
     return k;
 }
@@ -126,6 +149,7 @@ ieg_make_pbuffer(struct ieg_display *dpy, int w, int h)
                 ieg_dbg(1, "pbuffers need a current context here");
             }
         }
+        ieg_root_release(dpy);
     }
     return pb;
 }
@@ -279,6 +303,14 @@ ieg_probe(struct ieg_display *dpy)
         return 0;
     }
     dpy->root = G.glXCreateContextWithConfigSGIX(dpy->x, dpy->root_config->fb, GLX_RGBA_TYPE_SGIX, NULL, True);
+    /* Direct or indirect: SGI's GLX quietly makes every context indirect
+     * (rendered by an X server helper) when the display was opened by an
+     * Xlib other than IRIX's own /usr/lib32/libX11.so.1. */
+    if (ieg_debug >= 1 && dpy->root != NULL) {
+        Bool (*is_direct)(Display *, GLXContext) = (Bool (*)(Display *, GLXContext))dlsym(dpy->libgl, "glXIsDirect");
+        ieg_dbg(1, "display \"%s\", root context %p: %s", DisplayString(dpy->x), (void *)dpy->root,
+            is_direct ? (is_direct(dpy->x, dpy->root) ? "direct" : "INDIRECT") : "direct?");
+    }
     if (dpy->root == NULL) {
         ieg_fail("cannot create an OpenGL context on this display");
         return 0;
@@ -348,5 +380,6 @@ ieg_probe(struct ieg_display *dpy)
             c->bgra_by_matrix ? "colour matrix" : "CPU swap");
         ieg_log("GLX current is per %s", c->glx_current_per_thread ? "thread" : "process");
     }
+    ieg_root_release(dpy);
     return 1;
 }
