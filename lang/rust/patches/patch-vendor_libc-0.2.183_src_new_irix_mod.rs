$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- vendor/libc-0.2.183/src/new/irix/mod.rs.orig
+++ vendor/libc-0.2.183/src/new/irix/mod.rs
@@ -0,0 +1,5 @@
+//! SGI IRIX 6.5 libc.
+//!
+//! * Headers: those of IRIX 6.5.22 (N32), with the IRIX toolchain's wrappers.
+
+pub(crate) mod unistd;
