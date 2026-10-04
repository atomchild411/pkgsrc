$NetBSD$

IRIX 6.5 (N32): the mips64-sgi-irix target's module, as IRIX looks to the
IRIX toolchain (clang with its IRIX header wrappers and builtins).

--- src/new/irix/mod.rs.orig
+++ src/new/irix/mod.rs
@@ -0,0 +1,5 @@
+//! SGI IRIX 6.5 libc.
+//!
+//! * Headers: those of IRIX 6.5.22 (N32), with the IRIX toolchain's wrappers.
+
+pub(crate) mod unistd;
