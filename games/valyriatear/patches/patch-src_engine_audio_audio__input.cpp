$NetBSD$

Big-endian hosts use SDL_Swap32/16: include SDL_endian.h.

--- src/engine/audio/audio_input.cpp.orig
+++ src/engine/audio/audio_input.cpp
@@ -53,6 +53,7 @@
 /* Some quick macros for byte swapping. SDL has some nice fast asm methods, so we'll use those */
 // NOTE: these should probably be moved to the utils.h file
 #ifdef __BIG_ENDIAN__
+#include <SDL2/SDL_endian.h>
 #define SWAP_U32_FROM_LITTLE(x) { x = SDL_Swap32(x); }
 #define SWAP_U16_FROM_LITTLE(x) { x = SDL_Swap16(x); }
 #else
