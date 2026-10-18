$NetBSD: patch-lib_HTS__misc.c,v 1.1 2020/06/22 00:52:42 ryoon Exp $

* Add NetBSD workaround.
IRIX: fpos_t is a plain integer.

--- lib/HTS_misc.c.orig
+++ lib/HTS_misc.c
@@ -245,8 +245,10 @@
    } else if (fp->type == HTS_FILE) {
       fpos_t pos;
       fgetpos((FILE *) fp->pointer, &pos);
-#if defined(_WIN32) || defined(__CYGWIN__) || defined(__APPLE__) || defined(__ANDROID__)
+#if defined(_WIN32) || defined(__CYGWIN__) || defined(__APPLE__) || defined(__ANDROID__) || defined(__sgi)
       return (size_t) pos;
+#elif (__NetBSD__)
+      return (size_t) pos._pos;
 #else
       return (size_t) pos.__pos;
 #endif                          /* _WIN32 || __CYGWIN__ || __APPLE__ || __ANDROID__ */
