$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- openpty, forkpty and login_tty, with <pty.h> and <util.h>

--- lib/Headers/irix_wrappers/pty.h.orig
+++ lib/Headers/irix_wrappers/pty.h
@@ -0,0 +1,32 @@
+/*===---- pty.h - IRIX -------------------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * glibc's <pty.h> (and, through <util.h>, the BSDs'): openpty, forkpty and
+ * login_tty, which IRIX lacks; compiler-rt's IRIX builtins define them
+ * (irix/pty.c) on IRIX's _getpty().
+ */
+
+#ifndef __CLANG_IRIX_PTY_H
+#define __CLANG_IRIX_PTY_H
+
+#include <sys/types.h>
+#include <sys/ioctl.h>
+#include <termios.h>
+
+#ifdef __cplusplus
+extern "C" {
+#endif
+int openpty(int *, int *, char *, const struct termios *,
+            const struct winsize *);
+pid_t forkpty(int *, char *, const struct termios *, const struct winsize *);
+int login_tty(int);
+#ifdef __cplusplus
+}
+#endif
+
+#endif /* __CLANG_IRIX_PTY_H */
