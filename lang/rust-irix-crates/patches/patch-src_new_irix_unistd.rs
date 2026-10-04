$NetBSD$

IRIX 6.5 (N32): the mips64-sgi-irix target's module, as IRIX looks to the
IRIX toolchain (clang with its IRIX header wrappers and builtins).

--- src/new/irix/unistd.rs.orig
+++ src/new/irix/unistd.rs
@@ -0,0 +1,7 @@
+//! Header: `unistd.h`
+
+pub use crate::new::common::posix::unistd::{
+    STDERR_FILENO,
+    STDIN_FILENO,
+    STDOUT_FILENO,
+};
