$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/system_error.cpp.orig
+++ src/system_error.cpp
@@ -14,6 +14,7 @@
 #include <cstdio>
 #include <cstdlib>
 #include <cstring>
+#include <mutex>
 #include <optional>
 #include <string.h>
 #include <string>
@@ -154,6 +155,27 @@ string do_strerror_r(int ev) {
   std::snprintf(buffer, strerror_buff_size, "unknown error %d", ev);
   return string(buffer);
 }
+#  elif defined(__sgi)
+// IRIX has no strerror_r, and strerror may build its message in a buffer of
+// its own (the text comes from a message catalogue), so take turns.
+string do_strerror_r(int ev) {
+  static mutex strerror_mutex;
+  const int old_errno = errno;
+  string result;
+  {
+    lock_guard<mutex> lock(strerror_mutex);
+    const char* message = ::strerror(ev);
+    if (message != nullptr && message[0] != '\0')
+      result = message;
+  }
+  if (result.empty()) {
+    char buffer[strerror_buff_size];
+    std::snprintf(buffer, strerror_buff_size, "Unknown error %d", ev);
+    result = buffer;
+  }
+  errno = old_errno;
+  return result;
+}
 #  else
 
 // Only one of the two following functions will be used, depending on
