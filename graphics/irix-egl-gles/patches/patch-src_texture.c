$NetBSD$

From the author's repository, commit a667998: textures made without pixels
start clear, not with old graphics memory.

--- src/texture.c.orig
+++ src/texture.c
@@ -578,7 +578,14 @@
     t->ph = ctx->dpy->caps.npot ? height : pot(height);
     t->format = p.gl_format;
     ieg_bind_gl_texture(ctx, 0, t->gl);
-    G.glTexImage2D(GL_TEXTURE_2D, 0, p.gl_internal, t->pw, t->ph, 0, p.gl_format, GL_UNSIGNED_BYTE, NULL);
+    if (pixels == NULL) {
+        /* No contents given: GL leaves them undefined, and on SGI boards that is whatever the texture
+         * memory last held (another program's pictures). Start from transparent black instead. */
+        void *zero = calloc((size_t)t->pw * t->ph, 4);
+        G.glTexImage2D(GL_TEXTURE_2D, 0, p.gl_internal, t->pw, t->ph, 0, p.gl_format, GL_UNSIGNED_BYTE, zero);
+        free(zero);
+    } else
+        G.glTexImage2D(GL_TEXTURE_2D, 0, p.gl_internal, t->pw, t->ph, 0, p.gl_format, GL_UNSIGNED_BYTE, NULL);
     t->defined = 1;
     if (pixels != NULL) {
         upload(ctx, t, 0, 0, width, height, &p, pixels);
