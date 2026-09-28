$NetBSD: patch-hw_kdrive_ephyr_hostx.c,v 1.3 2021/06/24 18:43:08 tnn Exp $

Fix Xephyr visual with -parent option.

Drop the unused <err.h>, which IRIX does not have.

MIT-SHM: mark the segment for removal only after the host server has
attached it; System V systems other than Linux refuse to attach a segment
already marked, so SHM failed on them and every update went over the wire.

A host whose root visual is not TrueColor (IRIX's Xsgi: 8-bit
PseudoColor) showed the framebuffer in the wrong colours: use its 24-bit
TrueColor visual with a colormap of its own (not with -parent).

--- hw/kdrive/ephyr/hostx.c.orig
+++ hw/kdrive/ephyr/hostx.c
@@ -36,7 +36,6 @@
 #include <string.h>             /* for memset */
 #include <errno.h>
 #include <time.h>
-#include <err.h>
 
 #include <sys/ipc.h>
 #include <sys/shm.h>
@@ -69,6 +68,7 @@
     xcb_visualtype_t *visual;
     Window winroot;
     xcb_gcontext_t  gc;
+    xcb_colormap_t colormap;
     xcb_render_pictformat_t argb_format;
     xcb_cursor_t empty_cursor;
     xcb_generic_event_t *saved_event;
@@ -483,11 +483,14 @@
                 xcb_generic_error_t *error = NULL;
                 xcb_void_cookie_t cookie;
 
-                shmctl(shminfo->shmid, IPC_RMID, 0);
-
                 shminfo->shmseg = xcb_generate_id(HostX.conn);
                 cookie = xcb_shm_attach_checked(HostX.conn, shminfo->shmseg, shminfo->shmid, TRUE);
                 error = xcb_request_check(HostX.conn, cookie);
+
+                /* Only now: System V systems other than Linux let nobody
+                 * attach a segment already marked for removal, so the host
+                 * server could not attach it. */
+                shmctl(shminfo->shmid, IPC_RMID, 0);
 
                 if (error) {
                     free(error);
@@ -512,6 +515,26 @@
         shmdt(shminfo->shmaddr);
 
     shminfo->shmaddr = NULL;
+}
+
+/* The host's first 24-bit TrueColor visual, or NULL. */
+static xcb_visualtype_t *
+hostx_find_truecolor_visual(xcb_screen_t *xscreen)
+{
+    xcb_depth_iterator_t d;
+
+    for (d = xcb_screen_allowed_depths_iterator(xscreen); d.rem;
+         xcb_depth_next(&d)) {
+        xcb_visualtype_iterator_t v;
+
+        if (d.data->depth != 24)
+            continue;
+        for (v = xcb_depth_visuals_iterator(d.data); v.rem;
+             xcb_visualtype_next(&v))
+            if (v.data->_class == XCB_VISUAL_CLASS_TRUE_COLOR)
+                return v.data;
+    }
+    return NULL;
 }
 
 int
@@ -570,9 +593,38 @@
         }
     } else
 #endif
+    {
         HostX.visual = xcb_aux_find_visual_by_id(xscreen,xscreen->root_visual);
 
-    xcb_create_gc(HostX.conn, HostX.gc, HostX.winroot, 0, NULL);
+        /* A host whose root visual is not TrueColor (IRIX's Xsgi defaults
+         * to 8-bit PseudoColor) shows the framebuffer's pixel values
+         * through its default colormap, in the wrong colours. Use its
+         * 24-bit TrueColor visual instead, with a colormap of its own,
+         * unless a -parent window fixes the visual. */
+        if (HostX.visual->_class != XCB_VISUAL_CLASS_TRUE_COLOR) {
+            xcb_visualtype_t *tc = hostx_find_truecolor_visual(xscreen);
+
+            for (index = 0; tc && index < HostX.n_screens; index++) {
+                EphyrScrPriv *scrpriv = HostX.screens[index]->driver;
+
+                if (scrpriv->win_pre_existing != XCB_WINDOW_NONE)
+                    tc = NULL;
+            }
+            if (tc) {
+                HostX.visual = tc;
+                HostX.depth = 24;
+                HostX.colormap = xcb_generate_id(HostX.conn);
+                xcb_create_colormap(HostX.conn, XCB_COLORMAP_ALLOC_NONE,
+                                    HostX.colormap, HostX.winroot,
+                                    tc->visual_id);
+            }
+        }
+    }
+
+    /* A GC must match the depth of what it draws on; for a visual other
+     * than the root's it is made with the first window. */
+    if (!HostX.colormap)
+        xcb_create_gc(HostX.conn, HostX.gc, HostX.winroot, 0, NULL);
     cookie_WINDOW_STATE = xcb_intern_atom(HostX.conn, FALSE,
                                           strlen("_NET_WM_STATE"),
                                           "_NET_WM_STATE");
@@ -622,9 +674,28 @@
                               scrpriv->win_height,
                               0,
                               XCB_WINDOW_CLASS_COPY_FROM_PARENT,
-                              HostX.visual->visual_id,
+                              XCB_COPY_FROM_PARENT,
                               attr_mask,
                               attrs);
+        }
+        else if (HostX.colormap) {
+            /* Another depth than the root's: the border cannot be copied
+             * from the root, and the window needs the visual's colormap. */
+            uint32_t tc_attrs[3] = { 0, attrs[0], HostX.colormap };
+
+            xcb_create_window(HostX.conn,
+                              HostX.depth,
+                              scrpriv->win,
+                              HostX.winroot,
+                              0,0,100,100, /* will resize */
+                              0,
+                              XCB_WINDOW_CLASS_INPUT_OUTPUT,
+                              HostX.visual->visual_id,
+                              XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK |
+                              XCB_CW_COLORMAP,
+                              tc_attrs);
+            if (index == 0)
+                xcb_create_gc(HostX.conn, HostX.gc, scrpriv->win, 0, NULL);
         }
         else {
             xcb_create_window(HostX.conn,
@@ -637,6 +708,8 @@
                               HostX.visual->visual_id,
                               attr_mask,
                               attrs);
+        }
+        if (scrpriv->win_pre_existing == XCB_WINDOW_NONE) {
 
             hostx_set_win_title(screen,
                                 "(ctrl+shift grabs mouse and keyboard)");
@@ -693,6 +766,8 @@
 
     {
         xcb_alloc_color_cookie_t c = xcb_alloc_color(HostX.conn,
+                                                     HostX.colormap ?
+                                                     HostX.colormap :
                                                      xscreen->default_colormap,
                                                      red, green, blue);
         xcb_alloc_color_reply_t *r = xcb_alloc_color_reply(HostX.conn, c, NULL);
