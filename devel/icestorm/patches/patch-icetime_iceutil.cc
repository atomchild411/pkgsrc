$NetBSD: patch-icetime_iceutil.cc,v 1.2 2024/03/02 23:07:59 thorpej Exp $

On NetBSD, also use KERN_PROC_PATHNAME to get the path to the executable.
IRIX cannot tell a process its executable's path: use the installed one.

--- icetime/iceutil.cc.orig
+++ icetime/iceutil.cc
@@ -32,7 +32,7 @@
 #  include <unistd.h>
 #endif
 
-#ifdef __FreeBSD__
+#if defined(__FreeBSD__) || defined(__NetBSD__)
 #  include <sys/sysctl.h>
 #endif
 
@@ -51,10 +51,14 @@
 		buflen--;
 	return std::string(path, buflen);
 }
-#elif defined(__FreeBSD__)
+#elif defined(__FreeBSD__) || defined(__NetBSD__)
 std::string proc_self_dirname()
 {
+#ifdef __NetBSD__
+	int mib[4] = {CTL_KERN, KERN_PROC_ARGS, getpid(), KERN_PROC_PATHNAME};
+#else
 	int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
+#endif
 	size_t buflen;
 	char *buffer;
 	std::string path;
@@ -116,6 +120,12 @@
 		path += char(shortpath[i]);
 	return path;
 }
+#elif defined(__sgi)
+// IRIX cannot tell a process its executable's path: the installed one.
+std::string proc_self_dirname()
+{
+	return PREFIX "/bin/";
+}
 #elif defined(EMSCRIPTEN)
 std::string proc_self_dirname()
 {
