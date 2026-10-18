$NetBSD$

IRIX <math.h> defines ffloor; the big-endian part of byteptr.h needs doomtype.h.

--- src/doomdef.h.orig
+++ src/doomdef.h
@@ -95,6 +95,10 @@
 
 #define _USE_MATH_DEFINES // fixes M_PI errors in r_plane.c for Visual Studio
 #include <math.h>
+#ifdef __sgi
+// IRIX's <math.h> defines ffloor (to floorf), the name of SRB2's fake floors.
+#undef ffloor
+#endif
 
 #ifdef GETTEXT
 #include <libintl.h>
