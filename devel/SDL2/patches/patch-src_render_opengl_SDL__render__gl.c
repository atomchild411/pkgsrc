$NetBSD$

IRIX OpenGL 1.1: stand in glBlendFunc for the missing glBlendFuncSeparate,
and read pixels back as RGBA8888 (no GL_BGRA or _REV types for
glReadPixels), so the opengl renderer works instead of the software one.

--- src/render/opengl/SDL_render_gl.c.orig
+++ src/render/opengl/SDL_render_gl.c
@@ -235,15 +235,39 @@
 #define GL_CheckError(prefix, renderer) GL_CheckAllErrors(prefix, renderer, SDL_FILE, SDL_LINE, SDL_FUNCTION)
 #endif
 
+#ifdef __IRIX__
+/* IRIX's OpenGL is 1.1, without glBlendFuncSeparate (1.4). This renderer
+   blends only into the window there (no framebuffer objects, so no target
+   textures), where destination alpha is never seen: the colour factors are
+   enough. */
+static void (APIENTRY *GL_BlendFunc11)(GLenum, GLenum);
+
+static void APIENTRY GL_BlendFuncSeparate11(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
+{
+    GL_BlendFunc11(srcRGB, dstRGB);
+}
+
+#define SDL_PROC_FALLBACK(func)                                                               \
+        if (!data->func && GL_BlendFunc11 && SDL_strcmp(#func, "glBlendFuncSeparate") == 0) { \
+            data->func = (void *)GL_BlendFuncSeparate11;                                      \
+        }
+#else
+#define SDL_PROC_FALLBACK(func)
+#endif
+
 static int GL_LoadFunctions(GL_RenderData *data)
 {
 #ifdef __SDL_NOGETPROCADDR__
 #define SDL_PROC(ret, func, params) data->func = func;
 #else
     int retval = 0;
+#ifdef __IRIX__
+    GL_BlendFunc11 = SDL_GL_GetProcAddress("glBlendFunc");
+#endif
 #define SDL_PROC(ret, func, params)                                                           \
     do {                                                                                      \
         data->func = SDL_GL_GetProcAddress(#func);                                            \
+        SDL_PROC_FALLBACK(func)                                                               \
         if (!data->func) {                                                                    \
             retval = SDL_SetError("Couldn't load GL function %s: %s", #func, SDL_GetError()); \
         }                                                                                     \
@@ -424,6 +448,13 @@
         *format = GL_RGBA;
         *type = GL_UNSIGNED_INT_8_8_8_8_REV;
         break;
+#ifdef __IRIX__
+    case SDL_PIXELFORMAT_RGBA8888:
+        *internalFormat = GL_RGBA8;
+        *format = GL_RGBA;
+        *type = GL_UNSIGNED_INT_8_8_8_8;
+        break;
+#endif
     case SDL_PIXELFORMAT_YV12:
     case SDL_PIXELFORMAT_IYUV:
     case SDL_PIXELFORMAT_NV12:
@@ -1417,7 +1448,12 @@
                                Uint32 pixel_format, void *pixels, int pitch)
 {
     GL_RenderData *data = (GL_RenderData *)renderer->driverdata;
+#ifdef __IRIX__
+    /* IRIX's glReadPixels takes neither GL_BGRA nor the _REV types. */
+    Uint32 temp_format = renderer->target ? renderer->target->format : SDL_PIXELFORMAT_RGBA8888;
+#else
     Uint32 temp_format = renderer->target ? renderer->target->format : SDL_PIXELFORMAT_ARGB8888;
+#endif
     void *temp_pixels;
     int temp_pitch;
     GLint internalFormat;
