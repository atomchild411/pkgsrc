$NetBSD$

Cross builds cannot run the strcasestr test: use the bundled one.

--- ext/fileinfo/config.m4.orig
+++ ext/fileinfo/config.m4
@@ -46,6 +46,9 @@
     AC_MSG_RESULT(no)
     AC_MSG_NOTICE(using libmagic strcasestr implementation)
     libmagic_sources="$libmagic_sources libmagic/strcasestr.c"
+  ],[
+    AC_MSG_RESULT([no (cross-compiling)])
+    libmagic_sources="$libmagic_sources libmagic/strcasestr.c"
   ])
 
   PHP_NEW_EXTENSION(fileinfo, fileinfo.c $libmagic_sources, $ext_shared,,-I@ext_srcdir@/libmagic)
