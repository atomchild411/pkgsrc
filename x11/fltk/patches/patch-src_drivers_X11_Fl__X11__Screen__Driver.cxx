$NetBSD$

IRIX: SGI's ReadDisplay extension is in IRIX's libXext, not the modular
libXext fltk links with: read the screen with XGetImage, as elsewhere
(define FL_SGI_READDISPLAY to use it).

--- src/drivers/X11/Fl_X11_Screen_Driver.cxx.orig
+++ src/drivers/X11/Fl_X11_Screen_Driver.cxx
@@ -36,7 +36,7 @@
 #endif
 
 #  include <X11/Xutil.h>
-#  ifdef __sgi
+#  if defined(__sgi) && defined(FL_SGI_READDISPLAY)
 #    include <X11/extensions/readdisplay.h>
 #  else
 #    include <stdlib.h>
@@ -683,7 +683,7 @@
   int ws = Fl_Scalable_Graphics_Driver::floor(X+w, s) - Xs;
   int hs = Fl_Scalable_Graphics_Driver::floor(Y+h, s) - Ys;
 
-#  ifdef __sgi
+#  if defined(__sgi) && defined(FL_SGI_READDISPLAY)
   if (XReadDisplayQueryExtension(fl_display, &i, &i)) {
     image = XReadDisplay(fl_display, xid, Xs, Ys, ws, hs, 0, NULL);
   } else
