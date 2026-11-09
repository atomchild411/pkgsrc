$NetBSD$

Colours packed for big-endian CPUs too (R, G, B, A in memory, as
OpenGL and SDL read them); without this every colour is wrong on MIPS.

--- imgui.h.orig
+++ imgui.h
@@ -2985,6 +2985,14 @@
 #define IM_COL32_B_SHIFT    0
 #define IM_COL32_A_SHIFT    24
 #define IM_COL32_A_MASK     0xFF000000
+#elif defined(__BIG_ENDIAN__) || defined(__MIPSEB__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
+// Big-endian CPUs: R, G, B, A in memory, as OpenGL (GL_RGBA, GL_UNSIGNED_BYTE)
+// and SDL (SDL_Color, SDL_PIXELFORMAT_RGBA32) read vertex colours and textures.
+#define IM_COL32_R_SHIFT    24
+#define IM_COL32_G_SHIFT    16
+#define IM_COL32_B_SHIFT    8
+#define IM_COL32_A_SHIFT    0
+#define IM_COL32_A_MASK     0x000000FF
 #else
 #define IM_COL32_R_SHIFT    0
 #define IM_COL32_G_SHIFT    8
