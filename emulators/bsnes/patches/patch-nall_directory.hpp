$NetBSD$

IRIX: no d_type; fstatat() for every entry.

--- nall/directory.hpp.orig
+++ nall/directory.hpp
@@ -267,6 +267,11 @@
   }
 #else
   inline auto directoryIsFolder(DIR* dp, struct dirent* ep) -> bool {
+#if defined(__sgi)  //IRIX: no d_type
+    struct stat sp = {0};
+    fstatat(dirfd(dp), ep->d_name, &sp, 0);
+    return S_ISDIR(sp.st_mode);
+#else
     if(ep->d_type == DT_DIR) return true;
     if(ep->d_type == DT_LNK || ep->d_type == DT_UNKNOWN) {
       //symbolic links must be resolved to determine type
@@ -275,6 +280,7 @@
       return S_ISDIR(sp.st_mode);
     }
     return false;
+#endif
   }
 
   inline auto directory::create(const string& pathname, uint permissions) -> bool {
