$NetBSD$

IRIX: format with the C99 vsnprintf of clang's <stdio.h>, not IRIX's own,
which does not know the z, t, j and hh length modifiers (failed the libc
snprintf self-test at every start).

--- src/util/snprintf.cpp.orig	2026-11-19 21:35:26.728699265 +0000
+++ src/util/snprintf.cpp	2026-11-19 21:35:26.744699551 +0000
@@ -73,7 +73,13 @@
     else
         assert(max_size == 0);
 
+#if defined(__sgi) && defined(__clang__)
+    // IRIX: the C99 vsnprintf of clang's <stdio.h> (system_headers.h took its
+    // macro away); IRIX's own does not know z, t, j or hh.
+    long long len = __irix_vsnprintf(str, max_size, format, ap);
+#else
     long long len = vsnprintf(str, max_size, format, ap);
+#endif
     assert(len >= 0);
     assert(len < UPX_RSIZE_MAX_STR);
     size = (size_t) len + 1;
@@ -102,7 +108,13 @@
     else
         assert_noexcept(max_size == 0);
 
+#if defined(__sgi) && defined(__clang__)
+    // IRIX: the C99 vsnprintf of clang's <stdio.h> (system_headers.h took its
+    // macro away); IRIX's own does not know z, t, j or hh.
+    long long len = __irix_vsnprintf(str, max_size, format, ap);
+#else
     long long len = vsnprintf(str, max_size, format, ap);
+#endif
     assert_noexcept(len >= 0);
     assert_noexcept(len < UPX_RSIZE_MAX_STR);
     size = (size_t) len + 1;
