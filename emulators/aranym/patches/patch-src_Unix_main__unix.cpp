$NetBSD$

Only MIPSpro's old IRIX C++ headers declared signal handlers without the int argument.

--- src/Unix/main_unix.cpp.orig
+++ src/Unix/main_unix.cpp
@@ -129,7 +129,7 @@
 	exit(EXIT_FAILURE);
 }
 
-#ifdef OS_irix
+#if defined(OS_irix) && !defined(__clang__)
 void segmentationfault()
 #else
 void segmentationfault(int)
