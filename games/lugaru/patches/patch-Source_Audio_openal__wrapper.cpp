$NetBSD$

Decode Ogg Vorbis to native byte order on every big-endian CPU, not only
PowerPC: OpenAL takes 16-bit samples in native order (MIPS played static).

--- Source/Audio/openal_wrapper.cpp.orig
+++ Source/Audio/openal_wrapper.cpp
@@ -307,7 +307,7 @@
 
 static void* decode_to_pcm(const char* _fname, ALenum& format, ALsizei& size, ALuint& freq)
 {
-#ifdef __POWERPC__
+#if defined(__POWERPC__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
     const int bigendian = 1;
 #else
     const int bigendian = 0;
