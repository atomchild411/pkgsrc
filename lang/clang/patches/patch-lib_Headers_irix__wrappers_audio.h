$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- <audio.h>: IRIX 5's name for <dmedia/audio.h>

--- lib/Headers/irix_wrappers/audio.h.orig
+++ lib/Headers/irix_wrappers/audio.h
@@ -0,0 +1,19 @@
+/*===---- audio.h - IRIX: the Audio Library ---------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * IRIX 5's <audio.h>, the Audio Library (libaudio), which IRIX 6.5 keeps as
+ * <dmedia/audio.h>; code written for IRIX (gqmpeg, plib, snack, emiclock)
+ * still names the old one.
+ */
+
+#ifndef __CLANG_IRIX_AUDIO_H
+#define __CLANG_IRIX_AUDIO_H
+
+#include <dmedia/audio.h>
+
+#endif /* __CLANG_IRIX_AUDIO_H */
