$NetBSD$

IRIX audio driver (src/audio/irix): the Audio Library.

--- src/audio/SDL_sysaudio.h.orig
+++ src/audio/SDL_sysaudio.h
@@ -197,6 +197,7 @@
 extern AudioBootStrap PAUDIO_bootstrap;
 extern AudioBootStrap HAIKUAUDIO_bootstrap;
 extern AudioBootStrap COREAUDIO_bootstrap;
+extern AudioBootStrap IRIXAUDIO_bootstrap;
 extern AudioBootStrap DISKAUDIO_bootstrap;
 extern AudioBootStrap DUMMYAUDIO_bootstrap;
 extern AudioBootStrap FUSIONSOUND_bootstrap;
