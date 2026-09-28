$NetBSD$

Make softpipe's texture tile caches (256 KB each) on first use instead of
for all 6 shader stages x 128 sampler views at context creation: that was
192 MB per context, all of it touched where calloc zeroes (IRIX).

--- src/gallium/drivers/softpipe/sp_tex_tile_cache.c.orig
+++ src/gallium/drivers/softpipe/sp_tex_tile_cache.c
@@ -126,6 +126,9 @@
    struct pipe_resource *texture = view ? view->texture : NULL;
    uint i;
 
+   if (!tc)
+      return;
+
    assert(!tc->transfer);
 
    if (!sp_tex_tile_is_compat_view(tc, view)) {
@@ -167,7 +170,7 @@
 {
    int pos;
 
-   if (tc->texture) {
+   if (tc && tc->texture) {
       /* caching a texture, mark all entries as empty */
       for (pos = 0; pos < ARRAY_SIZE(tc->entries); pos++) {
          tc->entries[pos].addr.bits.invalid = 1;
