$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libunwind: find unwind tables through rld's object list

--- src/AddressSpace.hpp.orig
+++ src/AddressSpace.hpp
@@ -24,7 +24,9 @@
 #include "Registers.hpp"
 
 #ifndef _LIBUNWIND_USE_DLADDR
-  #if !(defined(_LIBUNWIND_IS_BAREMETAL) || defined(_WIN32) || defined(_AIX))
+  // IRIX (before 6.5.22 at least) has no dladdr.
+  #if !(defined(_LIBUNWIND_IS_BAREMETAL) || defined(_WIN32) || defined(_AIX) || \
+        defined(__sgi))
     #define _LIBUNWIND_USE_DLADDR 1
   #else
     #define _LIBUNWIND_USE_DLADDR 0
@@ -114,6 +116,11 @@ extern char __exidx_end;
 #include <windows.h>
 #include <psapi.h>
 
+#elif defined(_LIBUNWIND_USE_DL_ITERATE_PHDR) && defined(__sgi)
+
+// IRIX: dl_iterate_phdr over rld's object list.
+#include "irix_dl_iterate_phdr.h"
+
 #elif defined(_LIBUNWIND_USE_DL_ITERATE_PHDR) ||                               \
       defined(_LIBUNWIND_USE_DL_UNWIND_FIND_EXIDX)
 
