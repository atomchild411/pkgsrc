$NetBSD$

IRIX: wcsftime() takes a char format.

--- lib/time.cpp.orig
+++ lib/time.cpp
@@ -9,6 +9,18 @@
 
 #include <wchar.h>
 
+#if defined(__sgi)
+// IRIX's wcsftime() takes a char format (XPG4), not C99's wchar_t one.
+namespace {
+size_t c99_wcsftime(wchar_t* s, size_t max, wchar_t const* fmt, tm const* t)
+{
+	std::string const f = fz::to_string(std::wstring_view(fmt));
+	return ::wcsftime(s, max, f.c_str(), t);
+}
+}
+#define wcsftime c99_wcsftime
+#endif
+
 //#include <cassert>
 #define TIME_ASSERT(x) //assert(x)
 
