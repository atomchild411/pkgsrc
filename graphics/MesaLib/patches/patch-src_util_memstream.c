$NetBSD$

IRIX has no open_memstream: report failure, as on macOS.

--- src/util/memstream.c.orig
+++ src/util/memstream.c
@@ -51,7 +51,7 @@
    }
 
    return success;
-#elif defined(__APPLE__)
+#elif defined(__APPLE__) || defined(__sgi)
    return false;
 #else
    FILE *const f = open_memstream(bufp, sizep);
