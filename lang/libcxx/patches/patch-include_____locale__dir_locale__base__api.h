$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- include/__locale_dir/locale_base_api.h.orig
+++ include/__locale_dir/locale_base_api.h
@@ -121,6 +121,8 @@
 #    include <__locale_dir/support/fuchsia.h>
 #  elif defined(__linux__)
 #    include <__locale_dir/support/linux.h>
+#  elif defined(__sgi)
+#    include <__locale_dir/support/irix.h>
 #  else
 
 // TODO: This is a temporary definition to bridge between the old way we defined the locale base API
