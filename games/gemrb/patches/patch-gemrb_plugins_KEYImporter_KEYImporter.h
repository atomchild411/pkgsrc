$NetBSD$

Where size_t is 32 bits, the 64-bit key cannot initialize it in braces.

--- gemrb/plugins/KEYImporter/KEYImporter.h.orig
+++ gemrb/plugins/KEYImporter/KEYImporter.h
@@ -59,7 +59,7 @@
 
 struct MapKeyHash {
 	size_t operator()(const MapKey& key) const {
-		size_t h{key.type};
+		size_t h = static_cast<size_t>(key.type);
 		const char *c = key.ref.c_str();
 
 		for (unsigned int i = 0; *c && i < 9; ++i)
