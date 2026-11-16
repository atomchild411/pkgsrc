$NetBSD$

IRIX: play MIDI music (Doom's and Freedoom's) with the built-in OPL2
emulation by default; SDL_mixer has no synthesizer to use there, so the
music did not play (Error loading song).

--- src/m_misc.c.orig
+++ src/m_misc.c
@@ -444,6 +444,11 @@
 #ifdef _WIN32
   {"snd_midiplayer",{NULL, &snd_midiplayer},{0,"fluidsynth"},UL,UL,def_str,ss_none},
   {"snd_soundfont",{NULL, &snd_soundfont},{0,"TimGM6mb.sf2"},UL,UL,def_str,ss_none}, // soundfont name for synths that support it
+#elif defined(__sgi)
+  // IRIX: SDL_mixer has no MIDI synthesizer to play through there, so the
+  // built-in OPL2 emulation, which needs no instrument files.
+  {"snd_midiplayer",{NULL, &snd_midiplayer},{0,"opl2"},UL,UL,def_str,ss_none},
+  {"snd_soundfont",{NULL, &snd_soundfont},{0,"/usr/share/sounds/sf3/default-GM.sf3"},UL,UL,def_str,ss_none}, // soundfont name for synths that support it
 #else
   {"snd_midiplayer",{NULL, &snd_midiplayer},{0,"sdl"},UL,UL,def_str,ss_none},
   {"snd_soundfont",{NULL, &snd_soundfont},{0,"/usr/share/sounds/sf3/default-GM.sf3"},UL,UL,def_str,ss_none}, // soundfont name for synths that support it
