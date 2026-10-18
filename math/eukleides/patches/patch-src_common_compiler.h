$NetBSD$

IRIX defines NULL as 0L: cast through void * to the union.

--- src/common/compiler.h.orig
+++ src/common/compiler.h
@@ -48,8 +48,8 @@
 #define GTO(addr)	instruction(3, goto_addr, (_param)(addr))
 #define GSB(addr)	instruction(3, gosub_addr, (_param)(addr))
 #define JPZ(addr)	instruction(3, jump_if_zero, (_param)(addr))
-#define RTN		instruction(0, go_back, (_param)NULL)
-#define STP		instruction(0, stop, (_param)NULL)
-#define XEQ_(fct)	instruction(0, fct, (_param)NULL)
+#define RTN		instruction(0, go_back, (_param)(void *)NULL)
+#define STP		instruction(0, stop, (_param)(void *)NULL)
+#define XEQ_(fct)	instruction(0, fct, (_param)(void *)NULL)
 #define XEQ(fct,ptr)    instruction(1, fct, (_param)(void *)ptr)
 #define SET_(fct,lbl)   instruction(3, fct, (_param)(lbl))
