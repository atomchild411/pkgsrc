$NetBSD$

IRIX wcsftime takes a multibyte format (XPG4).

--- src/history.cpp.orig
+++ src/history.cpp
@@ -1065,8 +1065,14 @@
         if (localtime_r(&seconds, &timestamp)) {
             const int max_tstamp_length = 100;
             wchar_t timestamp_string[max_tstamp_length + 1];
+#ifdef __sgi
+            // IRIX's wcsftime is XPG4's: the format is a multibyte string.
+            if (std::wcsftime(timestamp_string, max_tstamp_length,
+                              wcs2string(show_time_format).c_str(), &timestamp) != 0) {
+#else
             if (std::wcsftime(timestamp_string, max_tstamp_length, show_time_format, &timestamp) !=
                 0) {
+#endif
                 result->append(timestamp_string);
             }
         }
