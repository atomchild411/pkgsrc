$NetBSD$

The colour-glyph hack interposes FreeType through dlsym(RTLD_NEXT), which IRIX does not have: build it only where it does.

--- gucharmap/main.c.orig
+++ gucharmap/main.c
@@ -49,6 +49,7 @@
  */
 
 #include <dlfcn.h>
+#ifdef RTLD_NEXT /* none on IRIX: no interposing there */
 #include <ft2build.h>
 #include FT_FREETYPE_H
 
@@ -94,6 +95,7 @@
   return original(face, char_code, load_flags & ~FT_LOAD_COLOR);
 }
 
+#endif /* RTLD_NEXT */
 /* END HACK */
 
 static gboolean
