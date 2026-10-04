$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- compiler/rustc_target/src/spec/base/irix.rs.orig
+++ compiler/rustc_target/src/spec/base/irix.rs
@@ -0,0 +1,20 @@
+use crate::spec::{Cc, LinkerFlavor, Lld, Os, TargetOptions, cvs};
+
+pub(crate) fn opts() -> TargetOptions {
+    TargetOptions {
+        os: Os::Irix,
+        vendor: "sgi".into(),
+        dynamic_linking: true,
+        families: cvs!["unix"],
+        has_rpath: true,
+        // Linked by clang (the IRIX toolchain is clang with lld), so GNU-style linker arguments.
+        linker_flavor: LinkerFlavor::Gnu(Cc::Yes, Lld::No),
+        // IRIX executables are not position independent.
+        position_independent_executables: false,
+        // Unwind tables everywhere, so backtraces work with panic=abort too.
+        default_uwtable: true,
+        // No thread-local storage in IRIX: std keeps its thread locals in pthread keys.
+        has_thread_local: false,
+        ..Default::default()
+    }
+}
