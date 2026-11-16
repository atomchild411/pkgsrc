$NetBSD$

Decode Ogg Vorbis to native byte order: the audio back ends take 16-bit
samples in native order, so big-endian CPUs played static.

--- gemrb/plugins/OGGReader/OGGReader.cpp.orig
+++ gemrb/plugins/OGGReader/OGGReader.cpp
@@ -107,7 +107,11 @@
 	int samples_got=0;
 	int samples_need=count;
 	while(samples_need) {
+		#if (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
+		int rd=ov_read(&OggStream, (char *)buffer, samples_need<<1, true, 2, 1, &whatisthis);
+#else
 		int rd=ov_read(&OggStream, (char *)buffer, samples_need<<1, false, 2, 1, &whatisthis);
+#endif
 		if(rd==OV_HOLE) {
 			continue;
 		}
