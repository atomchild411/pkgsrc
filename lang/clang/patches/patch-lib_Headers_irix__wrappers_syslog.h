$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Declare POSIX functions IRIX hides outside SGI mode
- Wrapper <syslog.h>: LOG_AUTHPRIV as LOG_AUTH

--- lib/Headers/irix_wrappers/syslog.h.orig
+++ lib/Headers/irix_wrappers/syslog.h
@@ -0,0 +1,36 @@
+/*===---- syslog.h - IRIX wrapper -------------------------------------------===
+ *
+ * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
+ * See https://llvm.org/LICENSE.txt for license information.
+ * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
+ *
+ *===-----------------------------------------------------------------------===
+ */
+
+#ifndef __CLANG_IRIX_SYSLOG_H
+#define __CLANG_IRIX_SYSLOG_H
+
+#include_next <syslog.h>
+
+/* The BSDs' and Linux's private authorization facility, which IRIX's
+ * syslogd does not know: send those messages to LOG_AUTH, as Solaris does
+ * (polkit). */
+#ifndef LOG_AUTHPRIV
+#define LOG_AUTHPRIV LOG_AUTH
+#endif
+
+/* POSIX's, in IRIX's libc, which its header declares only in SGI mode (and
+ * some X/Open modes): declared here outside SGI mode, with IRIX's own
+ * prototypes (found by compiling every POSIX header in six feature-macro
+ * modes against the 6.5.7 and 6.5.22 headers). */
+#if !_SGIAPI
+#ifdef __cplusplus
+extern "C" {
+#endif
+void vsyslog(int, const char *, __builtin_va_list);
+#ifdef __cplusplus
+}
+#endif
+#endif
+
+#endif /* __CLANG_IRIX_SYSLOG_H */
