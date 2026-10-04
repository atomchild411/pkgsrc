$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/unwind/src/lib.rs.orig
+++ library/unwind/src/lib.rs
@@ -193,6 +193,11 @@ unsafe extern "C" {}
 #[link(name = "unwind")]
 unsafe extern "C" {}
 
+// LLVM's libunwind, from the IRIX toolchain; static, so programs need no copy on the target.
+#[cfg(target_os = "irix")]
+#[link(name = "unwind", kind = "static", modifiers = "-bundle")]
+unsafe extern "C" {}
+
 #[cfg(target_os = "nto")]
 cfg_select! {
     target_env = "nto70" => {
