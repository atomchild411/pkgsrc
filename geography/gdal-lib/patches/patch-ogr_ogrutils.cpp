$NetBSD$

IRIX: <sys/param.h>'s roundup(x, y) macro; no d_type in struct dirent (as Solaris and Haiku).

--- ogr/ogrutils.cpp.orig
+++ ogr/ogrutils.cpp
@@ -71,6 +71,9 @@
 }
 
 // Round a string representing a number by 1 in the least significant digit.
+#ifdef roundup /* <sys/param.h>'s, on IRIX and the BSDs */
+#undef roundup
+#endif
 void roundup(std::string &s)
 {
     // Remove a negative sign if it exists to make processing
