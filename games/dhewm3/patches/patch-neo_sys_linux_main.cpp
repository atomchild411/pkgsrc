$NetBSD$

IRIX: have the kernel complete misaligned loads and stores (sysmips
MIPS_FIXADE), as other systems' CPUs or kernels do: more of the engine's
file and network code reads fields through casts at odd offsets, and real
IRIX otherwise ends the program with SIGBUS.

--- neo/sys/linux/main.cpp.orig
+++ neo/sys/linux/main.cpp
@@ -407,7 +407,16 @@
 main
 ===============
 */
+#ifdef __sgi
+extern "C" int sysmips(int, ...);
+#define MIPS_FIXADE	7	/* <sys/sysmips.h> */
+#endif
+
 int main(int argc, char **argv) {
+#ifdef __sgi
+	// IRIX: complete misaligned loads and stores instead of SIGBUS.
+	sysmips(MIPS_FIXADE, 1, 0, 0);
+#endif
 	// Prevent running Doom 3 as root
 	// Borrowed from Yamagi Quake II
 	if (getuid() == 0) {
