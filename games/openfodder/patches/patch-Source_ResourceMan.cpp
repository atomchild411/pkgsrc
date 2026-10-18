$NetBSD: patch-Source_ResourceMan.cpp,v 1.2 2025/08/19 11:29:40 wiz Exp $

Load static data from pkgsrc prefix.
IRIX's scandir() takes its callback without const (pre-POSIX 2008).

--- Source/ResourceMan.cpp.orig
+++ Source/ResourceMan.cpp
@@ -81,7 +81,7 @@
 		path = path1;
 		addBaseDir(path + "/.local/share/");
 	}
-	addBaseDir("/usr/local/share/");
+	addBaseDir("@PREFIX@/share/");
 #endif
 }
 
@@ -581,6 +581,13 @@
 	return cwd;
 }
 
+#ifdef __sgi
+// IRIX's scandir() predates POSIX 2008: same callback, without const.
+#define FILE_SELECT reinterpret_cast<int (*)(struct dirent *)>(file_select)
+#else
+#define FILE_SELECT file_select
+#endif
+
 int file_select(const struct dirent *entry) {
 	std::string name = entry->d_name;
 
@@ -605,7 +612,7 @@
 
 	transform(findType.begin(), findType.end(), findType.begin(), ::toupper);
 
-	int count = scandir(finalPath.str().c_str(), (dirent***)&directFiles, file_select, 0);
+	int count = scandir(finalPath.str().c_str(), (dirent***)&directFiles, FILE_SELECT, 0);
 
 	for (int i = 0; i < count; ++i) {
 
@@ -614,7 +621,7 @@
 
 	transform(findType.begin(), findType.end(), findType.begin(), ::tolower);
 
-	count = scandir(finalPath.str().c_str(), (dirent***)&directFiles, file_select, 0);
+	count = scandir(finalPath.str().c_str(), (dirent***)&directFiles, FILE_SELECT, 0);
 
 	for (int i = 0; i < count; ++i) {
 
