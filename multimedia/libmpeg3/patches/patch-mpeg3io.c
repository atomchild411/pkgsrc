$NetBSD$

Elsewhere (Linux, IRIX) keep <mntent.h>.

--- mpeg3io.c.orig
+++ mpeg3io.c
@@ -36,6 +36,10 @@
 # define fopen64 fopen
 # define fseeko64 fseek
 
+#else
+
+# include <mntent.h>
+
 #endif
 
 #include <sys/stat.h>
