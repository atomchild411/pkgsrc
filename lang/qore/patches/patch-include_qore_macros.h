$NetBSD$

MIPS (IRIX): the stack pointer, as for the other architectures.

--- include/qore/macros.h.orig
+++ include/qore/macros.h
@@ -54,6 +54,17 @@
 #include <qore/macros-riscv.h>
 #elif (defined(__s390__) || defined(__s390x__) || defined(__zarch__))
 #include <qore/macros-s390x.h>
+#elif defined(__mips__) && defined(__GNUC__)
+#ifndef _QORE_MACHINE_MACROS_H
+#define _QORE_MACHINE_MACROS_H
+#define STACK_DIRECTION_DOWN 1
+#define HAVE_CHECK_STACK_POS
+static inline size_t get_stack_pos() {
+    size_t addr;
+    __asm__("move %0, $sp" : "=r" (addr));
+    return addr;
+}
+#endif
 #endif
 
 #ifndef HAVE_CHECK_STACK_POS
