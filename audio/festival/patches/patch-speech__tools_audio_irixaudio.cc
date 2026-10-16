$NetBSD$

IRIX 6.5 keeps the AL headers under dmedia/.

--- speech_tools/audio/irixaudio.cc.orig
+++ speech_tools/audio/irixaudio.cc
@@ -18,7 +18,7 @@
 #include "EST_io_aux.h"
 
 #if defined (SUPPORT_IRIX) || defined (SUPPORT_IRIX53)
-#include <audio.h>
+#include <dmedia/audio.h>
 #include <unistd.h>
 
 int irix_supported = TRUE;
