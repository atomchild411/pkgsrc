$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- vendor/libc-0.2.183/src/new/irix/unistd.rs.orig
+++ vendor/libc-0.2.183/src/new/irix/unistd.rs
@@ -0,0 +1,7 @@
+//! Header: `unistd.h`
+
+pub use crate::new::common::posix::unistd::{
+    STDERR_FILENO,
+    STDIN_FILENO,
+    STDOUT_FILENO,
+};
