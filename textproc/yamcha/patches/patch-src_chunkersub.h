$NetBSD$

make_pair with explicit template arguments takes rvalues in libc++ (C++11 signature, also in C++03 mode): construct the pairs.

--- src/chunkersub.h.orig
+++ src/chunkersub.h
@@ -53,7 +53,7 @@
 	for (size_t n = 0; n < class_size; n++) {
 
 #ifdef _YAMCHA_PARSE_DETAIL
-	  dist[i].push_back (std::make_pair <char*, double>
+	  dist[i].push_back (std::pair <char*, double>
 			       (result[n].name, result[n].dist));
 #endif
 
@@ -70,7 +70,7 @@
 	for (size_t n = 0; n < class_size; n++) {
 
 #ifdef _YAMCHA_PARSE_DETAIL
-	  dist[i].push_back (std::make_pair <char*, double>
+	  dist[i].push_back (std::pair <char*, double>
 			     (result[n].name, result[n].dist));
 #endif
 	  
