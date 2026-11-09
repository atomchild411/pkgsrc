$NetBSD$

32-bit ImWchar, so that one library serves programs that show text
beyond the Basic Multilingual Plane (emoji).

--- imconfig.h.orig
+++ imconfig.h
@@ -70,7 +70,10 @@
 //#define IMGUI_USE_LEGACY_CRC32_ADLER
 
 //---- Use 32-bit for ImWchar (default is 16-bit) to support Unicode planes 1-16. (e.g. point beyond 0xFFFF like emoticons, dingbats, symbols, shapes, ancient languages, etc...)
-//#define IMGUI_USE_WCHAR32
+// pkgsrc: on, so that one library serves programs that need Unicode beyond the BMP.
+#ifndef IMGUI_USE_WCHAR32
+#define IMGUI_USE_WCHAR32
+#endif
 
 //---- Avoid multiple STB libraries implementations, or redefine path/filenames to prioritize another version
 // By default the embedded implementations are declared static and not available outside of Dear ImGui sources files.
