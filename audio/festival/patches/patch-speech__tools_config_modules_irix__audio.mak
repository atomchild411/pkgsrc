$NetBSD$

-L/usr/lib32 would name the build host's directory; the compiler finds IRIX's.

--- speech_tools/config/modules/irix_audio.mak.orig
+++ speech_tools/config/modules/irix_audio.mak
@@ -44,4 +44,4 @@
 
 AUDIO_DEFINES += -DSUPPORT_IRIX
 
-MODULE_LIBS += -L/usr/lib32 -laudio
+MODULE_LIBS += -laudio
