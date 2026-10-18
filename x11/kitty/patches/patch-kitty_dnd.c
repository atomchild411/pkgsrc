$NetBSD$

No d_type in struct dirent (IRIX): define the DT_ values, use the lstat() fallback.

--- kitty/dnd.c.orig
+++ kitty/dnd.c
@@ -17,6 +17,13 @@
 #include "kitty-verstable.h"
 #include <ctype.h>
 #include <dirent.h>
+#ifndef DT_UNKNOWN /* no d_type (IRIX): the lstat() fallback below */
+#define DT_UNKNOWN 0
+#define DT_DIR 4
+#define DT_REG 8
+#define DT_LNK 10
+#define KITTY_NO_D_TYPE
+#endif
 #include <fcntl.h>
 #include <limits.h>
 #include <stddef.h>
@@ -964,7 +971,11 @@
     while ((de = readdir(dir)) != NULL) {
         if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
 
+#ifdef KITTY_NO_D_TYPE
+        unsigned char dtype = DT_UNKNOWN;
+#else
         unsigned char dtype = de->d_type;
+#endif
         if (dtype == DT_UNKNOWN) {
             /* Fall back to lstat when d_type is unavailable */
             char full[PATH_MAX];
