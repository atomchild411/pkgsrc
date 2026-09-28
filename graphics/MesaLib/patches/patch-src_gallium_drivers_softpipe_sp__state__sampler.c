$NetBSD$

Make softpipe's texture tile caches (256 KB each) on first use instead of
for all 6 shader stages x 128 sampler views at context creation: that was
192 MB per context, all of it touched where calloc zeroes (IRIX).

--- src/gallium/drivers/softpipe/sp_state_sampler.c.orig
+++ src/gallium/drivers/softpipe/sp_state_sampler.c
@@ -125,6 +125,8 @@
       } else {
          pipe_sampler_view_reference(pview, views[i]);
       }
+      if (views[i] && !softpipe->tex_cache[shader][start + i])
+         softpipe->tex_cache[shader][start + i] = sp_create_tex_tile_cache(pipe);
       sp_tex_tile_cache_set_sampler_view(softpipe->tex_cache[shader][start + i],
                                          views[i]);
       /*
