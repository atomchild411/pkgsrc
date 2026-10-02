$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- <endian.h>, cfmakeraw, lchmod, get_nprocs

--- lib/Headers/irix_wrappers/endian.h.orig
+++ lib/Headers/irix_wrappers/endian.h
@@ -0,0 +1,16 @@
+/*===---- endian.h - IRIX wrapper --------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * IRIX has no <endian.h> (glibc, the BSDs, Solaris 11 do): IRIX's own
+ * <sys/endian.h> (after <standards.h>, which it requires) and the byte-order
+ * names and conversions it lacks.
+ */
+#ifndef __CLANG_IRIX_ENDIAN_H
+#define __CLANG_IRIX_ENDIAN_H
+#include <sys/endian.h>
+#endif /* __CLANG_IRIX_ENDIAN_H */
