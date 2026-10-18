$NetBSD$

IRIX's struct dirent has no d_type.

--- source/Irrlicht/CFileSystem.cpp.orig
+++ source/Irrlicht/CFileSystem.cpp
@@ -898,7 +898,7 @@
 					size = buf.st_size;
 					isDirectory = S_ISDIR(buf.st_mode);
 				}
-				#if !defined(_IRR_SOLARIS_PLATFORM_) && !defined(__CYGWIN__)
+				#if !defined(_IRR_SOLARIS_PLATFORM_) && !defined(__CYGWIN__) && !defined(__sgi)
 				// only available on some systems
 				else
 				{
