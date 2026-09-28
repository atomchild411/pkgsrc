$NetBSD$

Make softpipe's texture tile caches (256 KB each) on first use instead of
for all 6 shader stages x 128 sampler views at context creation: that was
192 MB per context, all of it touched where calloc zeroes (IRIX).

--- src/gallium/drivers/softpipe/sp_context.c.orig
+++ src/gallium/drivers/softpipe/sp_context.c
@@ -210,7 +210,7 @@
 {
    struct softpipe_screen *sp_screen = softpipe_screen(screen);
    struct softpipe_context *softpipe = CALLOC_STRUCT(softpipe_context);
-   uint i, sh;
+   uint i;
 
    util_init_math();
 
@@ -263,14 +263,8 @@
       softpipe->cbuf_cache[i] = sp_create_tile_cache( &softpipe->pipe );
    softpipe->zsbuf_cache = sp_create_tile_cache( &softpipe->pipe );
 
-   /* Allocate texture caches */
-   for (sh = 0; sh < ARRAY_SIZE(softpipe->tex_cache); sh++) {
-      for (i = 0; i < ARRAY_SIZE(softpipe->tex_cache[0]); i++) {
-         softpipe->tex_cache[sh][i] = sp_create_tex_tile_cache(&softpipe->pipe);
-         if (!softpipe->tex_cache[sh][i])
-            goto fail;
-      }
-   }
+   /* Texture caches (256 KB each) are made when a view is first bound to
+    * their slot (softpipe_set_sampler_views), not for all 6 x 128 slots. */
 
    softpipe->fs_machine = tgsi_exec_machine_create(PIPE_SHADER_FRAGMENT);
 
