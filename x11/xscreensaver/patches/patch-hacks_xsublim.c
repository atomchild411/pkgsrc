$NetBSD$

SgiUseSchemes is IRIX's Motif (libSgm), not in pkgsrc's X libraries: only with USE_SGI_SCHEMES.

--- hacks/xsublim.c.orig
+++ hacks/xsublim.c
@@ -104,7 +104,7 @@
 #include <X11/Xlib.h>
 #include <X11/Xos.h>
 #include <X11/Xproto.h>
-#if defined(__sgi)
+#if defined(__sgi) && defined(USE_SGI_SCHEMES)
 #include <X11/SGIScheme.h>
 #endif
 
@@ -387,7 +387,7 @@
         ya_rand_init (0);
 
 	/* Handle all the X nonsense */
-#if defined(__sgi)
+#if defined(__sgi) && defined(USE_SGI_SCHEMES)
 	SgiUseSchemes("none");
 #endif
 	for (arg_Count = 0;options[arg_Count].option != NULL;arg_Count++)
