$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/os/irix/mod.rs.orig
+++ library/std/src/os/irix/mod.rs
@@ -0,0 +1,6 @@
+//! IRIX specific definitions.
+
+#![stable(feature = "raw_ext", since = "1.1.0")]
+
+pub mod fs;
+pub mod raw;
