$NetBSD$

IRIX: a program that asks for target textures gets the software renderer
when the opengl one has none (no framebuffer objects in IRIX's OpenGL),
instead of an opengl renderer that fails at its first target texture.

--- src/render/SDL_render.c.orig
+++ src/render/SDL_render.c
@@ -1054,6 +1054,30 @@
         }
     }
 
+#ifdef __IRIX__
+    /* IRIX's OpenGL has no framebuffer objects, so the opengl renderer cannot
+       give target textures. A program that asks for them gets the software
+       renderer, which has them, instead of failing at its first target
+       texture ("Render targets not supported by OpenGL"). */
+    if ((flags & SDL_RENDERER_TARGETTEXTURE) &&
+        !(renderer->info.flags & SDL_RENDERER_TARGETTEXTURE)) {
+        for (index = 0; index < n; ++index) {
+            if (SDL_strcmp(render_drivers[index]->info.name, "software") == 0) {
+                break;
+            }
+        }
+        if (index < n) {
+            renderer->DestroyRenderer(renderer);
+            SDL_zerop(renderer);
+            renderer->magic = &renderer_magic;
+            rc = render_drivers[index]->CreateRenderer(renderer, window, flags & ~SDL_RENDERER_ACCELERATED);
+            if (rc == -1) {
+                goto error;
+            }
+        }
+    }
+#endif
+
     if (flags & SDL_RENDERER_PRESENTVSYNC) {
         renderer->wanted_vsync = SDL_TRUE;
 
