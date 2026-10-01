$NetBSD: patch-execinfo.c,v 1.3 2014/05/04 11:09:56 hauke Exp $

Fix the strings backtrace_symbols() returns.  IRIX: clang cannot give
__builtin_return_address() beyond the current frame on MIPS, so walk the
stack with the unwinder.

--- execinfo.c.orig	2004-07-19 05:21:09.000000000 +0000
+++ execinfo.c
@@ -36,8 +36,16 @@
 #include <string.h>
 #include <unistd.h>
 
+#ifdef __sun
+#include <alloca.h> 
+#endif
+
 #include "execinfo.h"
+#if defined(__sgi)
+#include <unwind.h>
+#else
 #include "stacktraverse.h"
+#endif
 
 #define D10(x) ceil(log10(((x) == 0) ? 2 : ((x) + 1)))
 
@@ -52,9 +60,50 @@
     return nptr;
 }
 
+#if defined(__sgi)
+/*
+ * IRIX: clang cannot give __builtin_return_address() beyond the current
+ * frame on MIPS (stacktraverse.c), so walk the stack with the unwinder
+ * instead (LLVM's libunwind, linked statically).  Frames without unwind
+ * tables end the walk.
+ */
+struct bt_state {
+    void **buffer;
+    int size, n, skip;
+};
+
+static _Unwind_Reason_Code
+bt_step(struct _Unwind_Context *ctx, void *arg)
+{
+    struct bt_state *st = arg;
+    void *pc = (void *)_Unwind_GetIP(ctx);
+
+    if (pc == NULL)
+        return _URC_END_OF_STACK;
+    if (st->skip > 0) {             /* backtrace() itself */
+        st->skip--;
+        return _URC_NO_REASON;
+    }
+    if (st->n == st->size)
+        return _URC_END_OF_STACK;
+    st->buffer[st->n++] = pc;
+    return _URC_NO_REASON;
+}
+
 int
 backtrace(void **buffer, int size)
 {
+    struct bt_state st = { buffer, size, 0, 1 };
+
+    if (size <= 0)
+        return 0;
+    _Unwind_Backtrace(bt_step, &st);
+    return st.n;
+}
+#else
+int
+backtrace(void **buffer, int size)
+{
     int i;
 
     for (i = 1; getframeaddr(i + 1) != NULL && i != size + 1; i++) {
@@ -65,20 +114,20 @@
 
     return i - 1;
 }
+#endif
 
 char **
 backtrace_symbols(void *const *buffer, int size)
 {
-    int i, clen, alen, offset;
+    size_t clen, alen;
+    int i, offset;
     char **rval;
-    char *cp;
     Dl_info info;
 
     clen = size * sizeof(char *);
     rval = malloc(clen);
     if (rval == NULL)
         return NULL;
-    (char **)cp = &(rval[size]);
     for (i = 0; i < size; i++) {
         if (dladdr(buffer[i], &info) != 0) {
             if (info.dli_sname == NULL)
@@ -92,14 +141,14 @@
                    2 +                      /* " <" */
                    strlen(info.dli_sname) + /* "function" */
                    1 +                      /* "+" */
-                   D10(offset) +            /* "offset */
+                   10 +                     /* "offset */
                    5 +                      /* "> at " */
                    strlen(info.dli_fname) + /* "filename" */
                    1;                       /* "\0" */
             rval = realloc_safe(rval, clen + alen);
             if (rval == NULL)
                 return NULL;
-            snprintf(cp, alen, "%p <%s+%d> at %s",
+            snprintf((char *) rval + clen, alen, "%p <%s+%d> at %s",
               buffer[i], info.dli_sname, offset, info.dli_fname);
         } else {
             alen = 2 +                      /* "0x" */
@@ -108,12 +157,15 @@
             rval = realloc_safe(rval, clen + alen);
             if (rval == NULL)
                 return NULL;
-            snprintf(cp, alen, "%p", buffer[i]);
+            snprintf((char *) rval + clen, alen, "%p", buffer[i]);
         }
-        rval[i] = cp;
-        cp += alen;
+        rval[i] = (char *) clen;
+        clen += alen;
     }
 
+    for (i = 0; i < size; i++)
+        rval[i] += (long) rval;
+
     return rval;
 }
 
