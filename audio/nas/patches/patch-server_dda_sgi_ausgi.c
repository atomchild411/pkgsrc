$NetBSD$

<audio.h>, not /usr/include/audio.h (a cross build's is elsewhere).

--- server/dda/sgi/ausgi.c.orig
+++ server/dda/sgi/ausgi.c
@@ -42,7 +42,7 @@
 #include <sys/param.h>
 
 /* SGI's AudioLibrary interface (avoid name conflict with NetAudio's audio.h */
-#include </usr/include/audio.h>
+#include <audio.h>	/* not by absolute path: a cross build's is elsewhere */
 
 #include <audio/audio.h>
 #include <audio/Aproto.h>
