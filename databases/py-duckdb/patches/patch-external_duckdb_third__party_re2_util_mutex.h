$NetBSD$

IRIX: no glibc <features.h>; re2 can use its POSIX reader/writer locks.

--- external/duckdb/third_party/re2/util/mutex.h.orig
+++ external/duckdb/third_party/re2/util/mutex.h
@@ -25,7 +25,7 @@
 #define _POSIX_C_SOURCE 200809L
 #endif
 #include <unistd.h>
-#if defined(_POSIX_READER_WRITER_LOCKS) && _POSIX_READER_WRITER_LOCKS > 0
+#if (defined(_POSIX_READER_WRITER_LOCKS) && _POSIX_READER_WRITER_LOCKS > 0) || defined(__sgi)
 #define MUTEX_IS_PTHREAD_RWLOCK
 #endif
 #endif
