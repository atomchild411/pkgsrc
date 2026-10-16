$NetBSD$

Where struct dirent has no d_type (IRIX), use the existing stat() path.

--- src/unix/FSNodePOSIX.cxx.orig
+++ src/unix/FSNodePOSIX.cxx
@@ -122,7 +122,7 @@ bool FilesystemNodePOSIX::getChildren(Ab
 
     FilesystemNodePOSIX entry(newPath, false);
 
-#if defined(SYSTEM_NOT_SUPPORTING_D_TYPE)
+#if defined(SYSTEM_NOT_SUPPORTING_D_TYPE) || !defined(DT_UNKNOWN)
     /* TODO: d_type is not part of POSIX, so it might not be supported
      * on some of our targets. For those systems where it isn't supported,
      * add this #elif case, which tries to use stat() instead.
