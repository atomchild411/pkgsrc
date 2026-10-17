$NetBSD$

audio.c defines update_sound; the no-sound driver duplicate breaks the link (IRIX uses it).

--- src/sd-none/sound.c.orig
+++ src/sd-none/sound.c
@@ -30,10 +30,6 @@
 {
 }
 
-void update_sound (int freq)
-{
-}
-
 void reset_sound (void)
 {
 }
