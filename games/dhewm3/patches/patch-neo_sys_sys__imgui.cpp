$NetBSD$

The built-in ImGui font data is little-endian 32-bit words: on big-endian
hosts (IRIX) AddFontFromMemoryCompressedTTF() read a garbage size and
asserted ("Incorrect value for font_data_size!"). Swap a copy there.

--- neo/sys/sys_imgui.cpp.orig
+++ neo/sys/sys_imgui.cpp
@@ -56,6 +56,28 @@
 
 #include "proggyvector_font.h"
 
+// binary_to_compressed_c wrote the font as 32-bit words for a little-endian
+// host: on a big-endian one each word's bytes come out reversed (the size in
+// the stream header is garbage and ImGui asserts), so hand ImGui a copy with
+// the bytes back in order.
+static const void* GetProggyVectorCompressedData()
+{
+#if (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || defined(__BIG_ENDIAN__) || defined(_MIPSEB)
+	static unsigned int swapped[sizeof(ProggyVector_compressed_data) / sizeof(ProggyVector_compressed_data[0])];
+	static bool done = false;
+	if ( !done ) {
+		for ( size_t i = 0; i < sizeof(swapped) / sizeof(swapped[0]); ++i ) {
+			unsigned int w = ProggyVector_compressed_data[i];
+			swapped[i] = (w >> 24) | ((w >> 8) & 0xff00u) | ((w << 8) & 0xff0000u) | (w << 24);
+		}
+		done = true;
+	}
+	return swapped;
+#else
+	return ProggyVector_compressed_data;
+#endif
+}
+
 static SDL_Window* sdlWindow = NULL;
 ImGuiContext* imguiCtx = NULL;
 static bool haveNewFrame = false;
@@ -334,7 +356,7 @@
 		strcpy( fontCfg.Name, "ProggyVector" );
 		float fontSize = 18.0f * GetScale();
 		float fontSizeInt = roundf( fontSize ); // font sizes are supposed to be rounded to integers
-		ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(ProggyVector_compressed_data, ProggyVector_compressed_size, fontSizeInt, nullptr);
+		ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(GetProggyVectorCompressedData(), ProggyVector_compressed_size, fontSizeInt, nullptr);
 	}
 
 	// Start the Dear ImGui frame
