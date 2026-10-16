$NetBSD$

IRIX's <nl_types.h> defines CMD_SET, which DOS_Shell has as a method.

--- include/shell.h.orig
+++ include/shell.h
@@ -40,6 +40,11 @@
  * by "external" programs. (config) */
 extern Program * first_shell;
 
+/* IRIX's <nl_types.h> defines CMD_SET (gencat's), the name of a method here. */
+#ifdef CMD_SET
+#undef CMD_SET
+#endif
+
 class DOS_Shell;
 
 class BatchFile {
