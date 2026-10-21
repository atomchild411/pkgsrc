$NetBSD$

IRIX: without d_type in struct dirent, every entry is of unknown type (as
for DT_UNKNOWN); configure finds optreset in <getopt.h>, which
line_tools.cpp does not include: declare it.

--- src/dar_suite/line_tools.cpp.orig
+++ src/dar_suite/line_tools.cpp
@@ -32,6 +32,11 @@
 #if HAVE_UNISTD_H
 #include <unistd.h>
 #endif
+#if HAVE_OPTRESET
+    // configure found it in <getopt.h>, which this file does not include
+    // (IRIX's compiler declares it there; dar's my_getopt_long.h clashes)
+extern int optreset;
+#endif
 #if HAVE_FCNTL_H
 #include <fcntl.h>
 #endif
