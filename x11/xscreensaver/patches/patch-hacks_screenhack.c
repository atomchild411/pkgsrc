$NetBSD$

SgiUseSchemes is IRIX's Motif (libSgm), not in pkgsrc's X libraries: only with USE_SGI_SCHEMES.

--- hacks/screenhack.c.orig
+++ hacks/screenhack.c
@@ -127,7 +127,7 @@
 #include <X11/StringDefs.h>
 #include <X11/keysym.h>
 
-#ifdef __sgi
+#if defined(__sgi) && defined(USE_SGI_SCHEMES)
 # include <X11/SGIScheme.h>	/* for SgiUseSchemes() */
 #endif /* __sgi */
 
@@ -780,7 +780,7 @@
 
   merge_options ();
 
-#ifdef __sgi
+#if defined(__sgi) && defined(USE_SGI_SCHEMES)
   /* We have to do this on SGI to prevent the background color from being
      overridden by the current desktop color scheme (we'd like our backgrounds
      to be black, thanks.)  This should be the same as setting the
