$NetBSD$

Prefer a deeper TrueColor visual to a palettized default one. Xsgi on SGI
hardware defaults to 8-bit PseudoColor with 24-bit TrueColor visuals
beside it, and SDL failed with "Palettized video modes are no longer
supported".

--- src/video/x11/SDL_x11modes.c.orig
+++ src/video/x11/SDL_x11modes.c
@@ -64,8 +64,23 @@
     depth = DefaultDepth(display, screen);
     if ((X11_UseDirectColorVisuals() &&
          X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
-        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
-        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
+        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo)) {
+        return 0;
+    }
+    /* A palettized default visual (Xsgi on SGI hardware: 8-bit
+       PseudoColor) usually comes with deeper TrueColor visuals; palettized
+       modes are not supported, so prefer those. */
+    {
+        static const int depths[] = { 24, 32, 16, 15, 12 };
+        int i;
+        for (i = 0; i < SDL_arraysize(depths); i++) {
+            if (depths[i] != depth &&
+                X11_XMatchVisualInfo(display, screen, depths[i], TrueColor, vinfo)) {
+                return 0;
+            }
+        }
+    }
+    if (X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
         X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
         return 0;
     }
