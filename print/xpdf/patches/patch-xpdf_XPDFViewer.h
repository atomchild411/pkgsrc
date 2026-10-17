$NetBSD$

SGI's Sgm paned window only where its header is (IRIX without the Sgm
development headers uses the Motif 1.x code path).

--- xpdf/XPDFViewer.h.orig
+++ xpdf/XPDFViewer.h
@@ -21,7 +21,7 @@
 #include "gtypes.h"
 #include "XPDFCore.h"
 
-#if (XmVERSION <= 1) && !defined(__sgi)
+#if (XmVERSION <= 1) && !(defined(__sgi) && __has_include(<Sgm/HPanedW.h>))
 #define DISABLE_OUTLINE
 #endif
 
