$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the target's module, IRIX as the IRIX toolchain (clang with its IRIX
header wrappers and builtins) sees it.

--- libc-0.2.189/src/new/irix/mod.rs.orig
+++ libc-0.2.189/src/new/irix/mod.rs
@@ -0,0 +1,5 @@
+//! SGI IRIX 6.5 libc.
+//!
+//! * Headers: those of IRIX 6.5.22 (N32), with the IRIX toolchain's wrappers.
+
+pub(crate) mod unistd;
