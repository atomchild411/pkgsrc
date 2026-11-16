$NetBSD$

Big-endian CPUs: Cairo's RGB24 pixels are native-endian 32-bit words
(0x00RRGGBB), so they need no byte swap; the swapped values lost blue
(white showed as yellow).

--- ui/gtk3/gtkdisplay.c.orig
+++ ui/gtk3/gtkdisplay.c
@@ -161,10 +161,14 @@
       gtkdisplay_colours[i] =  red << 24 | green << 16 | blue << 8;
       break;
     case FORMAT_x8r8g8b8:
-      gtkdisplay_colours[i] = blue << 24 | green << 16 |  red << 8;
+      /* Cairo's RGB24 pixels are native-endian 32-bit words */
+      gtkdisplay_colours[i] = red << 16 | green << 8 | blue;
       break;
     }
 
+    if( format == FORMAT_x8r8g8b8 )
+              bw_colours[i] = grey |  grey << 8 | grey << 16;
+    else
               bw_colours[i] = grey << 24 |  grey << 16 | grey << 8;
 
 #else                           /* #ifdef WORDS_BIGENDIAN */
