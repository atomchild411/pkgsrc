$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- POSIX 2008 string, stdio, memory and time functions
- POSIX 2008's *at() calls and fdopendir
- Declare POSIX functions IRIX hides outside SGI mode

--- lib/Headers/irix_wrappers/dirent.h.orig
+++ lib/Headers/irix_wrappers/dirent.h
@@ -0,0 +1,44 @@
+/*===---- dirent.h - IRIX wrapper -------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * dirfd (POSIX 2008), which IRIX lacks: compiler-rt's irix/posix2008.c
+ * returns the DIR's descriptor.
+ */
+
+#ifndef __CLANG_IRIX_DIRENT_H
+#define __CLANG_IRIX_DIRENT_H
+
+#include_next <dirent.h>
+
+#ifdef __cplusplus
+extern "C" {
+#endif
+int dirfd(DIR *);
+DIR *fdopendir(int); /* irix/atfile.c */
+#ifdef __cplusplus
+}
+#endif
+
+/* POSIX's, in IRIX's libc, which its header declares only in SGI mode (and
+ * some X/Open modes): declared here outside SGI mode, with IRIX's own
+ * prototypes (found by compiling every POSIX header in six feature-macro
+ * modes against the 6.5.7 and 6.5.22 headers). */
+#if !_SGIAPI
+struct dirent;
+#ifdef __cplusplus
+extern "C" {
+#endif
+int alphasort(struct dirent **, struct dirent **);
+int scandir(const char *, struct dirent ***, int (*)(struct dirent *),
+            int (*)(struct dirent **, struct dirent **));
+#ifdef __cplusplus
+}
+#endif
+#endif
+
+#endif /* __CLANG_IRIX_DIRENT_H */
