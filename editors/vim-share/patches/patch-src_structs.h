$NetBSD$

IRIX's <sys/fcntl.h> defines OP_NONE (an oplock state) under _SGIAPI; vim
never uses oplocks, so let its enum have the name.  (From the hand-built vim
9.1 proven on IRIX.)

--- src/structs.h.orig
+++ src/structs.h
@@ -636,6 +636,11 @@
 /*
  * :set operator types
  */
+// IRIX's <sys/fcntl.h> defines OP_NONE, an oplock state for F_OPLKSTAT, as a
+// macro under _SGIAPI; vim never uses oplocks, so let the enum have the name.
+#ifdef OP_NONE
+# undef OP_NONE
+#endif
 typedef enum {
     OP_NONE = 0,
     OP_ADDING,		// "opt+=arg"
