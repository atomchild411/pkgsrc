$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry as is
already done for DT_UNKNOWN.

--- src/Directory.cpp.orig
+++ src/Directory.cpp
@@ -108,7 +108,7 @@ bool Directory::remove_directory (const
           !strcmp (de->d_name, ".."))
         continue;
 
-#if defined (SOLARIS) || defined (HAIKU)
+#if defined (SOLARIS) || defined (HAIKU) || !defined (DT_UNKNOWN)
       struct stat s;
       lstat ((dir + "/" + de->d_name).c_str (), &s);
       if (S_ISDIR (s.st_mode))
@@ -219,6 +219,14 @@ void Directory::list (
         list (base + "/" + de->d_name, results, recursive);
       else
         results.push_back (base + "/" + de->d_name);
+#elif !defined (DT_UNKNOWN)
+      // No d_type (e.g. IRIX): lstat() each entry, as for DT_UNKNOWN below.
+      struct stat s;
+      if (recursive && lstat ((base + "/" + de->d_name).c_str (), &s) == 0 &&
+          S_ISDIR (s.st_mode))
+        list (base + "/" + de->d_name, results, recursive);
+      else
+        results.push_back (base + "/" + de->d_name);
 #else
       if (recursive && de->d_type == DT_UNKNOWN)
       {
