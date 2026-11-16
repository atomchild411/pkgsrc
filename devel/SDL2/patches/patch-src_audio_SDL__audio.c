$NetBSD$

IRIX audio driver (src/audio/irix): the Audio Library, before the
disk and dummy drivers.

--- src/audio/SDL_audio.c.orig
+++ src/audio/SDL_audio.c
@@ -129,6 +129,9 @@
 #ifdef SDL_AUDIO_DRIVER_OS2
     &OS2AUDIO_bootstrap,
 #endif
+#ifdef SDL_AUDIO_DRIVER_IRIX
+    &IRIXAUDIO_bootstrap,
+#endif
 #ifdef SDL_AUDIO_DRIVER_DISK
     &DISKAUDIO_bootstrap,
 #endif
