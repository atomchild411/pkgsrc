$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Declare POSIX functions IRIX hides outside SGI mode

--- lib/Headers/irix_wrappers/pwd.h.orig
+++ lib/Headers/irix_wrappers/pwd.h
@@ -0,0 +1,33 @@
+/*===---- pwd.h - IRIX wrapper ----------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ */
+
+#ifndef __CLANG_IRIX_PWD_H
+#define __CLANG_IRIX_PWD_H
+
+#include <sys/types.h>
+#include_next <pwd.h>
+
+/* POSIX's, in IRIX's libc, which its header declares only in SGI mode (and
+ * some X/Open modes): declared here outside SGI mode, with IRIX's own
+ * prototypes (found by compiling every POSIX header in six feature-macro
+ * modes against the 6.5.7 and 6.5.22 headers). */
+#if !_SGIAPI
+struct passwd;
+#ifdef __cplusplus
+extern "C" {
+#endif
+void endpwent(void);
+struct passwd *getpwent(void);
+void setpwent(void);
+#ifdef __cplusplus
+}
+#endif
+#endif
+
+#endif /* __CLANG_IRIX_PWD_H */
