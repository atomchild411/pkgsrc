$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- <sched.h>: no MIN, MAX or TICK leaking into C++ from <sys/param.h>

--- lib/Headers/irix_wrappers/sched.h.orig
+++ lib/Headers/irix_wrappers/sched.h
@@ -0,0 +1,35 @@
+/*===---- sched.h - IRIX wrapper --------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * IRIX's <sched.h> includes <sys/sched.h>, which in SGI mode includes
+ * <sys/param.h>, so every program that includes <pthread.h> -- in C++ all
+ * that include libc++'s thread-aware headers (<list>, <queue>, <mutex>, ...)
+ * -- gets its MIN, MAX and TICK macros, which glibc's <sched.h> does not
+ * give. C++ code that names a function or member MIN, MAX or TICK then fails
+ * (freeimage, clustalw, espeak-ng). In C++, when <sys/param.h> came in only
+ * this way, take those three back; the <sys/param.h> wrapper defines them
+ * again on any later #include of it. C is left as it was.
+ */
+
+#ifndef __CLANG_IRIX_SCHED_H
+#define __CLANG_IRIX_SCHED_H
+
+#if defined(__cplusplus) && !defined(_SYS_PARAM_H)
+#define __CLANG_IRIX_SCHED_PARAM
+#endif
+
+#include_next <sched.h>
+
+#ifdef __CLANG_IRIX_SCHED_PARAM
+#undef __CLANG_IRIX_SCHED_PARAM
+#undef MIN
+#undef MAX
+#undef TICK
+#endif
+
+#endif /* __CLANG_IRIX_SCHED_H */
