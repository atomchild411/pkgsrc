$NetBSD$

IRIX's <sys/fcntl.h> defines OP_NONE (an oplock state).

--- src/nvim/option_defs.h.orig
+++ src/nvim/option_defs.h
@@ -75,6 +75,11 @@ typedef struct {
   OptValData data;
 } OptVal;
 
+// IRIX's <sys/fcntl.h> names an oplock state OP_NONE.
+#ifdef OP_NONE
+# undef OP_NONE
+#endif
+
 /// :set operator types
 typedef enum {
   OP_NONE = 0,
