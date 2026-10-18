$NetBSD$

IRIX <sys/bsd_types.h> has a quad typedef: rename the function.

--- kitty/decorations.c.orig
+++ kitty/decorations.c
@@ -1202,7 +1202,7 @@
 }
 
 static void
-quad(Canvas *self, Corner which) {
+quad_block(Canvas *self, Corner which) {
     uint x = which & LEFT_EDGE ? 0 : 1, y = which & TOP_EDGE ? 0 : 1;
     uint num_cols = self->width / 2;
     uint left = x * num_cols;
@@ -1220,7 +1220,7 @@
 quads(Canvas *self, ...) {
     va_list args; va_start(args, self);
     int which;
-    while ((which = va_arg(args, int))) quad(self, which);
+    while ((which = va_arg(args, int))) quad_block(self, which);
     va_end(args);
 }
 
@@ -1978,10 +1978,10 @@
         S(L'🮘', cross_shade, false);
         S(L'🮙', cross_shade, true);
 
-        C(L'▖', quad, BOTTOM_LEFT);
-        C(L'▗', quad, BOTTOM_RIGHT);
-        C(L'▘', quad, TOP_LEFT);
-        C(L'▝', quad, TOP_RIGHT);
+        C(L'▖', quad_block, BOTTOM_LEFT);
+        C(L'▗', quad_block, BOTTOM_RIGHT);
+        C(L'▘', quad_block, TOP_LEFT);
+        C(L'▝', quad_block, TOP_RIGHT);
         C(L'▙', quads, TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, 0);
         C(L'▚', quads, TOP_LEFT, BOTTOM_RIGHT, 0);
         C(L'▛', quads, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, 0);
