$NetBSD$

IRIX: the executable path from argv[0] and PATH, as on OpenBSD (no /proc/self/exe).

--- kernel/driver.cc.orig
+++ kernel/driver.cc
@@ -214,7 +214,7 @@
 #endif
 }
 
-#if defined(__OpenBSD__)
+#if defined(__OpenBSD__) || defined(__sgi)
 namespace Yosys {
 extern char *yosys_argv0;
 extern char yosys_path[PATH_MAX];
@@ -584,7 +584,7 @@
 	if (print_stats)
 		log_hasher = new SHA1;
 
-#if defined(__OpenBSD__)
+#if defined(__OpenBSD__) || defined(__sgi)
 	// save the executable origin for proc_self_dirname()
 	yosys_argv0 = argv[0];
 	realpath(yosys_argv0, yosys_path);
