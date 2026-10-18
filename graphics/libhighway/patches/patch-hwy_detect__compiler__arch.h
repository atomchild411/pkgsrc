$NetBSD$

Architectures it has no SIMD for (MIPS, SPARC, ...) are allowed, but had no vector size.

--- hwy/detect_compiler_arch.h.orig
+++ hwy/detect_compiler_arch.h
@@ -442,7 +442,8 @@
 #elif HWY_ARCH_PPC || HWY_ARCH_S390X || HWY_ARCH_ARM_V7 || HWY_ARCH_ARM_OLD
 #define HWY_ARCH_MAX_BYTES 16
 #else
-#error "Missing case for HWY_ARCH_*"
+/* None of the above (MIPS, SPARC, ...): scalar/EMU128 only. */
+#define HWY_ARCH_MAX_BYTES 16
 #endif
 
 //------------------------------------------------------------------------------
