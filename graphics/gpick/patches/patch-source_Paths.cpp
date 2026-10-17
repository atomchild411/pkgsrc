$NetBSD: patch-source_Paths.cpp,v 1.1 2024/10/04 04:17:38 ryoon Exp $
IRIX has no /proc/self/exe: the installed path (@PREFIX@, by SUBST).

--- source/Paths.cpp.orig
+++ source/Paths.cpp
@@ -36,7 +36,7 @@
 		std::runtime_error(message) {
 	}
 };
-#if BOOST_OS_LINUX != 0
+#if BOOST_OS_LINUX != 0 || BOOST_OS_BSD_NET != 0
 static std::string getExecutablePath() {
 	std::vector<char> buffer;
 	buffer.resize(4096);
@@ -63,6 +63,11 @@
 		buffer.resize(buffer.size() * 2);
 	}
 }
+#elif defined(__sgi)
+// IRIX has no /proc/self/exe: where it is installed.
+static std::string getExecutablePath() {
+	return "@PREFIX@/bin/gpick";
+}
 #else
 #error getExecutablePath not implemented for current OS
 #endif
