$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- compiler/rustc_target/src/spec/targets/mips64_sgi_irix.rs.orig
+++ compiler/rustc_target/src/spec/targets/mips64_sgi_irix.rs
@@ -0,0 +1,30 @@
+use rustc_abi::Endian;
+
+use crate::spec::{Arch, CfgAbi, LlvmAbi, Target, TargetMetadata, TargetOptions, base, cvs};
+
+pub(crate) fn target() -> Target {
+    Target {
+        // Rust's LLVM has no IRIX OS; the N32 Linux triple stands in (same object format and
+        // calling convention, and the IRIX toolchain links the result).
+        llvm_target: "mips64-unknown-linux-gnuabin32".into(),
+        metadata: TargetMetadata {
+            description: Some("MIPS IV IRIX 6.5, N32 ABI".into()),
+            tier: Some(3),
+            host_tools: Some(false),
+            std: Some(true),
+        },
+        pointer_width: 32,
+        data_layout: "E-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128".into(),
+        arch: Arch::Mips64,
+        options: TargetOptions {
+            cfg_abi: CfgAbi::AbiN32,
+            endian: Endian::Big,
+            cpu: "mips4".into(),
+            features: "+mips4".into(),
+            max_atomic_width: Some(64),
+            llvm_abiname: LlvmAbi::N32,
+            llvm_args: cvs!["-mno-check-zero-division"],
+            ..base::irix::opts()
+        },
+    }
+}
