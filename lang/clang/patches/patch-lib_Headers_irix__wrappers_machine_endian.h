$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Wrappers: <sys/queue.h>, <machine/endian.h>, SUN_LEN, I, IPPROTO_SCTP

--- lib/Headers/irix_wrappers/machine/endian.h.orig
+++ lib/Headers/irix_wrappers/machine/endian.h
@@ -0,0 +1,16 @@
+/*===---- machine/endian.h - IRIX wrapper ------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * The BSDs' and macOS's name for the byte-order header, which IRIX does not
+ * have: the same as <sys/endian.h>.
+ */
+
+#ifndef __CLANG_IRIX_MACHINE_ENDIAN_H
+#define __CLANG_IRIX_MACHINE_ENDIAN_H
+#include <sys/endian.h>
+#endif /* __CLANG_IRIX_MACHINE_ENDIAN_H */
