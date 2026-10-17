$NetBSD: patch-xpdf_XPDFViewer.cc,v 1.1 2012/03/21 17:05:58 hans Exp $
SGI's Sgm paned window only where its header is (IRIX without the Sgm
development headers uses the Motif 1.x code path).

--- xpdf/XPDFViewer.cc.orig
+++ xpdf/XPDFViewer.cc
@@ -20,7 +20,7 @@
 #ifdef HAVE_X11_XPM_H
 #include <X11/xpm.h>
 #endif
-#if defined(__sgi) && (XmVERSION <= 1)
+#if (defined(__sgi) && __has_include(<Sgm/HPanedW.h>)) && (XmVERSION <= 1)
 #define Object XtObject
 #include <Sgm/HPanedW.h>
 #undef Object
@@ -134,7 +134,7 @@
 //------------------------------------------------------------------------
 
 struct ZoomMenuInfo {
-  const char *label;
+  char *label;
   double zoom;
 };
 
@@ -1917,7 +1917,7 @@
   // paned window
   n = 0;
   XtSetArg(args[n], XmNorientation, XmHORIZONTAL); ++n;
-#if defined(__sgi) && (XmVERSION <= 1)
+#if (defined(__sgi) && __has_include(<Sgm/HPanedW.h>)) && (XmVERSION <= 1)
   panedWin = SgCreateHorzPanedWindow(parent, "panedWin", args, n);
 #else
   panedWin = XmCreatePanedWindow(parent, "panedWin", args, n);
@@ -1930,7 +1930,7 @@
   XtSetArg(args[n], XmNallowResize, True); ++n;
   XtSetArg(args[n], XmNpaneMinimum, 1); ++n;
   XtSetArg(args[n], XmNpaneMaximum, 10000); ++n;
-#if !(defined(__sgi) && (XmVERSION <= 1))
+#if !((defined(__sgi) && __has_include(<Sgm/HPanedW.h>)) && (XmVERSION <= 1))
   XtSetArg(args[n], XmNwidth, 1); ++n;
 #endif
   XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); ++n;
