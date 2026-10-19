$NetBSD$

IRIX 6.5: <sys/stropts.h> and <dmedia/audio.h>.

--- audio/SGIaudio.c.orig
+++ audio/SGIaudio.c
@@ -61,12 +61,12 @@
 #include <sys/stat.h>
 #include <sys/fcntl.h>
 #include <sys/signal.h>
-#include <sys/strops.h>
+#include <sys/stropts.h>	/* IRIX 6.5 (I_FLUSH) */
 
 
 #include "include/error.h"
 #include "include/audio.h"
-#include <audio.h>            /* SGI audio interface lib. header */
+#include <dmedia/audio.h>     /* SGI audio interface lib. header */
 #include "include/ulaw.h"
 
 /*
