$NetBSD$

IRIX has no <arpa/nameser_compat.h>: its <arpa/nameser.h> keeps the old names.

--- libinfinity/common/inf-name-resolver.c.orig
+++ libinfinity/common/inf-name-resolver.c
@@ -61,7 +61,9 @@
 #else
 # include <resolv.h>
 # include <arpa/nameser.h>
-# include <arpa/nameser_compat.h>
+# if !defined(__has_include) || __has_include(<arpa/nameser_compat.h>)
+#  include <arpa/nameser_compat.h>
+# endif
 #endif
 
 #include <errno.h>
