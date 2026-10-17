$NetBSD$

MIPS: the trampolines take the block in $a1 and its argument in $a2
(SARG0/SARG1, as on the other architectures; the MIPS branch left them
undefined).

--- block_trampolines.S.orig
+++ block_trampolines.S
@@ -98,6 +98,8 @@
 #define ARG0 $a0
 #define ARG1 $a1
 #define ARG2 $a2
+#define SARG0 ARG1
+#define SARG1 ARG2
 
 #elif defined(__powerpc__)
 ////////////////////////////////////////////////////////////////////////////////
