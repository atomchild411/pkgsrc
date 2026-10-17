$NetBSD$

IRIX: the executable path from argv[0] and PATH, as on OpenBSD (no /proc/self/exe).

--- kernel/yosys.cc.orig
+++ kernel/yosys.cc
@@ -972,7 +972,7 @@
 {
 	return "/";
 }
-#elif defined(__OpenBSD__) || defined(__HAIKU__)
+#elif defined(__OpenBSD__) || defined(__HAIKU__) || defined(__sgi)
 char yosys_path[PATH_MAX];
 char *yosys_argv0;
 
