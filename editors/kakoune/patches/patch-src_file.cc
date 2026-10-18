$NetBSD$

IRIX cannot tell a process its executable's path: use the installed one, as on OpenBSD.

--- src/file.cc.orig
+++ src/file.cc
@@ -450,7 +450,7 @@
         buffer[res] = '\0';
         return buffer;
     }
-#elif defined(__OpenBSD__)
+#elif defined(__OpenBSD__) || defined(__sgi)
     (void)buffer;
     return KAK_BIN_PATH;
 #elif defined(__sun__)
