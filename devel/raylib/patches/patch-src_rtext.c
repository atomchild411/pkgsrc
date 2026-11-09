$NetBSD$

The default font's gray and alpha written as bytes: as shorts they came
out swapped on big-endian CPUs (IRIX), every glyph in an opaque black box.

--- src/rtext.c.orig
+++ src/rtext.c
@@ -241,13 +241,10 @@
     {
         for (int j = 31; j >= 0; j--)
         {
-            if (BIT_CHECK(defaultFontData[counter], j))
-            {
-                // NOTE: We are unreferencing data as short, so,
-                // we must consider data as little-endian order (alpha + gray)
-                ((unsigned short *)imFont.data)[i + j] = 0xffff;
-            }
-            else ((unsigned short *)imFont.data)[i + j] = 0x00ff;
+            // Gray then alpha, written as bytes: the same on big-endian CPUs
+            // (a short 0x00ff there is gray 0, alpha 255: opaque black)
+            ((unsigned char *)imFont.data)[(i + j)*2] = 0xff;
+            ((unsigned char *)imFont.data)[(i + j)*2 + 1] = BIT_CHECK(defaultFontData[counter], j)? 0xff : 0x00;
         }
 
         counter++;
