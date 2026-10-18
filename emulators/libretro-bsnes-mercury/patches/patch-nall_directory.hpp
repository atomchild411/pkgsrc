$NetBSD$

IRIX: no d_type either; stat() as on Haiku and Solaris.

--- nall/directory.hpp.orig
+++ nall/directory.hpp
@@ -190,7 +190,7 @@
       while((ep = readdir(dp))) {
         if(!strcmp(ep->d_name, ".")) continue;
         if(!strcmp(ep->d_name, "..")) continue;
-#if defined(__HAIKU__) || defined(__sun)
+#if defined(__HAIKU__) || defined(__sun) || defined(__sgi)
 		struct stat sp = {0};
         stat(ep->d_name, &sp);
         bool is_directory = S_ISDIR(sp.st_mode);
@@ -222,7 +222,7 @@
       while((ep = readdir(dp))) {
         if(!strcmp(ep->d_name, ".")) continue;
         if(!strcmp(ep->d_name, "..")) continue;
-#if defined(__HAIKU__) || defined(__sun)
+#if defined(__HAIKU__) || defined(__sun) || defined(__sgi)
         struct stat sp = {0};
         stat(ep->d_name, &sp);
         if(!S_ISDIR(sp.st_mode)) {
