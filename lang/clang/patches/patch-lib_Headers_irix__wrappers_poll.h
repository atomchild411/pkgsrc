$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- BSD and glibc names: <paths.h>, <poll.h>, <arpa/telnet.h>, <sys/cdefs.h>, <dlfcn.h>

--- lib/Headers/irix_wrappers/poll.h.orig
+++ lib/Headers/irix_wrappers/poll.h
@@ -0,0 +1,22 @@
+/*===---- poll.h - IRIX wrapper ----------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * INFTIM, the BSDs' name for poll's "wait forever" timeout (-1), which
+ * IRIX's <poll.h> lacks.
+ */
+
+#ifndef __CLANG_IRIX_POLL_H
+#define __CLANG_IRIX_POLL_H
+
+#include_next <poll.h>
+
+#ifndef INFTIM
+#define INFTIM (-1)
+#endif
+
+#endif /* __CLANG_IRIX_POLL_H */
