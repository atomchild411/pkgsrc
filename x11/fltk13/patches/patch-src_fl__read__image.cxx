$NetBSD$

IRIX's ReadDisplay extension comes with SGI's own X libraries; the ones fltk
links (pkgsrc's) do not have it: read images the generic way.

--- src/fl_read_image.cxx.orig
+++ src/fl_read_image.cxx
@@ -171,7 +171,7 @@
 #  include "fl_read_image_win32.cxx" // gives the WIN32 version of read_win_rectangle()
 #else
 #  include <X11/Xutil.h>
-#  ifdef __sgi
+#  if defined(__sgi) && defined(HAVE_XREADDISPLAY)
 #    include <X11/extensions/readdisplay.h>
 #  else
 #    include <stdlib.h>
@@ -246,7 +246,7 @@
   int allow_outside = w < 0;    // negative w allows negative X or Y, that is, window frame
   if (w < 0) w = - w;
 
-#  ifdef __sgi
+#  if defined(__sgi) && defined(HAVE_XREADDISPLAY)
   if (XReadDisplayQueryExtension(fl_display, &i, &i)) {
     image = XReadDisplay(fl_display, fl_window, X, Y, w, h, 0, NULL);
   } else
