$NetBSD$

SGI's OpenGL (IRIX): font atlas updates widened to 32-texel columns
(High and Maximum IMPACT refuse narrower subimages, and draw no text),
the atlas capped at 1024 texels; flat shapes drawn with texturing off
(where IRIX textures in software); an alpha test where blending does
not happen (IMGUI_GL_ALPHA_TEST=1/0 decides instead).

--- backends/imgui_impl_opengl2.cpp.orig
+++ backends/imgui_impl_opengl2.cpp
@@ -55,6 +55,11 @@
 #ifndef IMGUI_DISABLE
 #include "imgui_impl_opengl2.h"
 #include <stdint.h>     // intptr_t
+#if defined(__sgi)
+#include <stdlib.h>     // getenv, atoi
+// SGI's OpenGL (IRIX): see the IMGUI_IMPL_OPENGL2_SGI parts below.
+#define IMGUI_IMPL_OPENGL2_SGI
+#endif
 
 // Clang/GCC warnings with -Weverything
 #if defined(__clang__)
@@ -91,6 +96,9 @@
 {
     bool        UseTexParameterToSetSampler;
     GLuint      NextSampler;
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+    int         Blending;       // 0: not tried yet, 1: works, 2: does not (alpha test instead)
+#endif
 
     ImGui_ImplOpenGL2_Data() { memset((void*)this, 0, sizeof(*this)); }
 };
@@ -110,6 +118,78 @@
     IM_UNUSED(bd);
 }
 
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+// High and Maximum IMPACT refuse (GL_INVALID_VALUE) a texture subimage unless
+// its right side is a multiple of 32 and it is 32 texels wide or more
+// (glTexSubImage2D(3G), MACHINE DEPENDENCIES; IRIX 6.5.22's libGLcore checks
+// both, even at the texture's right edge). Columns x..x+w-1 of a texture tw
+// wide, widened to those terms: Dear ImGui keeps every texel of the atlas, so
+// the added columns go up as the texture already has them.
+static void ImGui_ImplOpenGL2_Aligned32(int& x, int& w, int tw)
+{
+    int right = (x + w + 31) & ~31;
+    if (right > tw)
+        right = tw;
+    int left = right - 32 < x ? right - 32 : x;
+    if (left < 0)
+        left = 0;
+    x = left;
+    w = right - left;
+}
+
+// Whether blending happens (it does not on some boards and emulators): one
+// pixel at the lower left corner, cleared to black, a transparent white quad
+// blended over it, read back; then the pixel is put back as it was.
+static bool ImGui_ImplOpenGL2_BlendingWorks(int fb_width, int fb_height)
+{
+    unsigned char keep[4] = { 0, 0, 0, 0 }, px[4] = { 0, 0, 0, 0 };
+    glPushAttrib(GL_ALL_ATTRIB_BITS);
+    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
+    glPixelStorei(GL_PACK_ALIGNMENT, 1);
+    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
+    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
+    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
+    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, keep);
+    glDisable(GL_TEXTURE_2D);
+    glDisable(GL_DEPTH_TEST);
+    glDisable(GL_STENCIL_TEST);
+    glDisable(GL_ALPHA_TEST);
+    glDisable(GL_LIGHTING);
+    glDisable(GL_CULL_FACE);
+    glDisable(GL_FOG);
+    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
+    glMatrixMode(GL_PROJECTION);
+    glPushMatrix();
+    glLoadIdentity();
+    glOrtho(0, fb_width, 0, fb_height, -1, 1);
+    glMatrixMode(GL_MODELVIEW);
+    glPushMatrix();
+    glLoadIdentity();
+    glEnable(GL_SCISSOR_TEST);
+    glScissor(0, 0, 1, 1);
+    glClearColor(0, 0, 0, 1);
+    glClear(GL_COLOR_BUFFER_BIT);
+    glEnable(GL_BLEND);
+    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
+    glColor4ub(255, 255, 255, 0);
+    glBegin(GL_QUADS);
+    glVertex2f(0, 0); glVertex2f(8, 0); glVertex2f(8, 8); glVertex2f(0, 8);
+    glEnd();
+    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
+    glDisable(GL_BLEND);
+    glPixelZoom(1, 1);
+    glRasterPos2i(0, 0);
+    glDrawPixels(1, 1, GL_RGBA, GL_UNSIGNED_BYTE, keep);
+    glMatrixMode(GL_MODELVIEW);
+    glPopMatrix();
+    glMatrixMode(GL_PROJECTION);
+    glPopMatrix();
+    glPopClientAttrib();
+    glPopAttrib();
+    return px[0] < 64;
+}
+#endif
+
 static void ImGui_ImplOpenGL2_SetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height)
 {
     // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers, polygon fill.
@@ -132,6 +212,15 @@
     glShadeModel(GL_SMOOTH);
     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     bd->NextSampler = GL_LINEAR;
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+    // Where blending does not happen, an alpha test keeps the right pixels
+    // (rougher text edges). IMGUI_GL_ALPHA_TEST=1 or 0 decides it instead.
+    if (bd->Blending == 2)
+    {
+        glEnable(GL_ALPHA_TEST);
+        glAlphaFunc(GL_GREATER, 0.3f);
+    }
+#endif
 
     // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
     // you may need to backup/reset/restore other state, e.g. for current shader using the commented lines below.
@@ -180,6 +269,18 @@
             if (tex->Status != ImTextureStatus_OK)
                 ImGui_ImplOpenGL2_UpdateTexture(tex);
 
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+    if (bd->Blending == 0)
+        bd->Blending = ImGui_ImplOpenGL2_BlendingWorks(fb_width, fb_height) ? 1 : 2;
+    // Flat shapes (all three corners on the font atlas's white texel) are
+    // drawn with texturing off: where IRIX textures in software (Newport, XZ,
+    // Solid IMPACT, Octane SI) texturing them was nearly all of a frame's time.
+    ImFontAtlas* atlas = ImGui::GetIO().Fonts;
+    const ImTextureID atlas_tex = atlas->TexData ? atlas->TexData->GetTexID() : ImTextureID_Invalid;
+    const ImVec2 white = atlas->TexUvWhitePixel;
+    bool texturing = true;
+#endif
+
     // Backup GL state
     GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
     GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
@@ -212,7 +313,12 @@
             {
                 // User callback, registered via ImDrawList::AddCallback()
                 if (pcmd->UserCallback == ImGui_ImplOpenGL2_DrawCallback_ResetRenderState)
+                {
                     ImGui_ImplOpenGL2_SetupRenderState(draw_data, fb_width, fb_height);
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+                    texturing = true;
+#endif
+                }
                 else
                     pcmd->UserCallback(draw_list, pcmd);
             }
@@ -239,7 +345,44 @@
                     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, bd->NextSampler);
                 }
 
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+                // Runs of triangles, textured or (on the atlas's white texel) not.
+                const GLenum idx_type = sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
+                const ImDrawIdx* first = idx_buffer + pcmd->IdxOffset;
+                const ImDrawVert* vtx = vtx_buffer + pcmd->VtxOffset;
+                const bool on_atlas = pcmd->GetTexID() == atlas_tex;
+                const unsigned int n = pcmd->ElemCount;
+                unsigned int start = 0;
+                while (start < n)
+                {
+                    bool flat = false;
+                    unsigned int end = n;
+                    if (on_atlas)
+                    {
+                        // A triangle is flat when its three corners are on the white texel.
+                        #define IMGUI_SGI_FLAT(T) (vtx[first[(T)]].uv.x == white.x && vtx[first[(T)]].uv.y == white.y && \
+                                                   vtx[first[(T) + 1]].uv.x == white.x && vtx[first[(T) + 1]].uv.y == white.y && \
+                                                   vtx[first[(T) + 2]].uv.x == white.x && vtx[first[(T) + 2]].uv.y == white.y)
+                        flat = IMGUI_SGI_FLAT(start);
+                        end = start + 3;
+                        while (end < n && IMGUI_SGI_FLAT(end) == flat)
+                            end += 3;
+                        #undef IMGUI_SGI_FLAT
+                    }
+                    if (flat == texturing)
+                    {
+                        texturing = !flat;
+                        if (texturing)
+                            glEnable(GL_TEXTURE_2D);
+                        else
+                            glDisable(GL_TEXTURE_2D);
+                    }
+                    glDrawElements(GL_TRIANGLES, (GLsizei)(end - start), idx_type, first + start);
+                    start = end;
+                }
+#else
                 glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer + pcmd->IdxOffset);
+#endif
             }
         }
     }
@@ -309,7 +452,15 @@
         GL_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, tex->Width));
         GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
         for (ImTextureRect& r : tex->Updates)
+        {
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+            int x = r.x, w = r.w;
+            ImGui_ImplOpenGL2_Aligned32(x, w, tex->Width);
+            GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, x, r.y, w, r.h, GL_RGBA, GL_UNSIGNED_BYTE, tex->GetPixelsAt(x, r.y)));
+#else
             GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, r.x, r.y, r.w, r.h, GL_RGBA, GL_UNSIGNED_BYTE, tex->GetPixelsAt(r.x, r.y)));
+#endif
+        }
         GL_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
         GL_CALL(glBindTexture(GL_TEXTURE_2D, last_texture)); // Restore state
         tex->SetStatus(ImTextureStatus_OK);
@@ -361,6 +512,24 @@
     platform_io.DrawCallback_SetSamplerLinear = ImGui_ImplOpenGL2_DrawCallback_SetSamplerLinear;
     platform_io.DrawCallback_SetSamplerNearest = ImGui_ImplOpenGL2_DrawCallback_SetSamplerNearest;
 
+#ifdef IMGUI_IMPL_OPENGL2_SGI
+    // Font atlas no bigger than the board takes, nor than 1024 (texture
+    // memory is small on these boards: 1 MB on High IMPACT).
+    GLint max_tex = 0;
+    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex);
+    int cap = (max_tex > 0 && max_tex < 1024) ? (int)max_tex : 1024;
+    if (io.Fonts->TexMaxWidth > cap)
+        io.Fonts->TexMaxWidth = cap;
+    if (io.Fonts->TexMaxHeight > cap)
+        io.Fonts->TexMaxHeight = cap;
+    if (io.Fonts->TexMinWidth > cap)
+        io.Fonts->TexMinWidth = cap;
+    if (io.Fonts->TexMinHeight > cap)
+        io.Fonts->TexMinHeight = cap;
+    const char* alpha_test = getenv("IMGUI_GL_ALPHA_TEST");
+    bd->Blending = alpha_test ? (atoi(alpha_test) ? 2 : 1) : 0;
+#endif
+
     return true;
 }
 
