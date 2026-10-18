$NetBSD$

IRIX's struct dirent has no d_type.

--- irr/src/CFileSystem.cpp.orig
+++ irr/src/CFileSystem.cpp
@@ -429,7 +429,7 @@
 					size = buf.st_size;
 					isDirectory = S_ISDIR(buf.st_mode);
 				}
-#if !defined(_IRR_SOLARIS_PLATFORM_) && !defined(__CYGWIN__) && !defined(__HAIKU__)
+#if !defined(_IRR_SOLARIS_PLATFORM_) && !defined(__CYGWIN__) && !defined(__HAIKU__) && !defined(__sgi)
 				// only available on some systems
 				else {
 					isDirectory = dirEntry->d_type == DT_DIR;
