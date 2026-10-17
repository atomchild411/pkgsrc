$NetBSD$

readelf's own fseek64 under a name of its own: IRIX's <stdio.h> declares
fseek64 (a static definition after an extern declaration does not compile).

--- binutils/readelf.c.orig
+++ binutils/readelf.c
@@ -365,6 +365,9 @@
   symbol_public
 };
 
+/* IRIX's <stdio.h> declares an fseek64 of its own.  */
+#define fseek64 readelf_fseek64
+
 static int
 fseek64 (FILE *stream, int64_t offset, int whence)
 {
