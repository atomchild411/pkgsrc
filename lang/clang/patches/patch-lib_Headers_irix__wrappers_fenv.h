$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- The C95/C99 library IRIX 6.5.7 lacks, and wide characters in libc++
- headers: work against a stock IRIX 6.5.22 root too
- <fenv.h>: our fenv outside C99 mode
- Wrapper <fenv.h>: always C99's functions, never MIPSpro's draft

--- lib/Headers/irix_wrappers/fenv.h.orig
+++ lib/Headers/irix_wrappers/fenv.h
@@ -0,0 +1,58 @@
+/*===---- fenv.h - IRIX wrapper ---------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ *
+ * IRIX's own <fenv.h> comes only with MIPSpro 7.3/7.4's headers, and is a
+ * draft of C99's: feclearexcept, fegetexceptflag, feraiseexcept,
+ * fesetexceptflag, fegetenv, fesetenv and feupdateenv return void, and all
+ * of them are optional (a stock 6.5.22 libm has none). Code written to C99
+ * (hdf5: `if (feclearexcept(FE_INVALID) != 0)`) does not compile against it.
+ * Never use it: declare C99's functions, as compiler-rt implements them
+ * (irix/fenv.c) on the FPU's control and status register.
+ */
+
+#ifndef __CLANG_IRIX_FENV_H
+#define __CLANG_IRIX_FENV_H
+
+/* The values are the register's fields as the MIPS architecture defines
+ * them: the flag bits and the rounding mode. */
+typedef unsigned int fenv_t;    /* the whole control and status register */
+typedef unsigned int fexcept_t; /* its flag bits */
+
+#define FE_INEXACT 0x04
+#define FE_UNDERFLOW 0x08
+#define FE_OVERFLOW 0x10
+#define FE_DIVBYZERO 0x20
+#define FE_INVALID 0x40
+#define FE_ALL_EXCEPT 0x7c
+
+#define FE_TONEAREST 0
+#define FE_TOWARDZERO 1
+#define FE_UPWARD 2
+#define FE_DOWNWARD 3
+
+#ifdef __cplusplus
+extern "C" {
+#endif
+extern const fenv_t __irix_fe_dfl_env;
+#define FE_DFL_ENV (&__irix_fe_dfl_env)
+int feclearexcept(int) __asm__("__irix_feclearexcept");
+int fegetexceptflag(fexcept_t *, int) __asm__("__irix_fegetexceptflag");
+int feraiseexcept(int) __asm__("__irix_feraiseexcept");
+int fesetexceptflag(const fexcept_t *, int) __asm__("__irix_fesetexceptflag");
+int fetestexcept(int) __asm__("__irix_fetestexcept");
+int fegetround(void) __asm__("__irix_fegetround");
+int fesetround(int) __asm__("__irix_fesetround");
+int fegetenv(fenv_t *) __asm__("__irix_fegetenv");
+int feholdexcept(fenv_t *) __asm__("__irix_feholdexcept");
+int fesetenv(const fenv_t *) __asm__("__irix_fesetenv");
+int feupdateenv(const fenv_t *) __asm__("__irix_feupdateenv");
+#ifdef __cplusplus
+}
+#endif
+
+#endif /* __CLANG_IRIX_FENV_H */
