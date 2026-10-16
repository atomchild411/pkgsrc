$NetBSD$

Where struct dirent has no d_type (IRIX), lstat() each entry as is
already done for DT_UNKNOWN.

--- src/libshared/src/FS.cpp.orig
+++ src/libshared/src/FS.cpp
@@ -963,7 +963,7 @@ bool Directory::remove_directory (const
           ! strcmp (de->d_name, ".."))
         continue;
 
-#if defined (SOLARIS) || defined (HAIKU)
+#if defined (SOLARIS) || defined (HAIKU) || !defined (DT_UNKNOWN)
       struct stat s;
       if (lstat ((dir + '/' + de->d_name).c_str (), &s))
         throw format ("lstat error {1}: {2}", errno, strerror (errno));
@@ -1079,6 +1079,18 @@ void Directory::list (
       if (recursive && S_ISDIR (s.st_mode))
         list (base + '/' + de->d_name, results, recursive);
       else
+        results.push_back (base + '/' + de->d_name);
+#elif !defined (DT_UNKNOWN)
+      // No d_type (e.g. IRIX): lstat() each entry, as for DT_UNKNOWN below.
+      struct stat s;
+      if (recursive)
+      {
+        if (lstat ((base + '/' + de->d_name).c_str (), &s))
+          throw format ("lstat error {1}: {2}", errno, strerror (errno));
+      }
+      if (recursive && S_ISDIR (s.st_mode))
+        list (base + '/' + de->d_name, results, recursive);
+      else
         results.push_back (base + '/' + de->d_name);
 #else
       if (recursive && de->d_type == DT_UNKNOWN)
