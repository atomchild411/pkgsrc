$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the target's module, IRIX as the IRIX toolchain (clang with its IRIX
header wrappers and builtins) sees it.

--- libc-0.2.189/src/new/irix/unistd.rs.orig
+++ libc-0.2.189/src/new/irix/unistd.rs
@@ -0,0 +1,7 @@
+//! Header: `unistd.h`
+
+pub use crate::new::common::posix::unistd::{
+    STDERR_FILENO,
+    STDIN_FILENO,
+    STDOUT_FILENO,
+};
