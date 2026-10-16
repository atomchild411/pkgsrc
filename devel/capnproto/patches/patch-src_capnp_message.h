$NetBSD$

IRIX (n32): 4-byte pointers with 8-byte-aligned 64-bit members, so a
ReaderArena takes 152 bytes, not 148: one more word, as on 32-bit Darwin.

--- src/capnp/message.h.orig
+++ src/capnp/message.h
@@ -127,7 +127,7 @@
 private:
   ReaderOptions options;
 
-#if defined(__EMSCRIPTEN__) || (defined(__APPLE__) && (defined(__ppc__) || defined(__i386__)))
+#if defined(__EMSCRIPTEN__) || (defined(__APPLE__) && (defined(__ppc__) || defined(__i386__))) || defined(__sgi)
   static constexpr size_t arenaSpacePadding = 19;
 #else
   static constexpr size_t arenaSpacePadding = 18;
