$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- compiler/rustc_target/src/spec/base/mod.rs.orig
+++ compiler/rustc_target/src/spec/base/mod.rs
@@ -14,6 +14,7 @@ pub(crate) mod hermit;
 pub(crate) mod hurd;
 pub(crate) mod hurd_gnu;
 pub(crate) mod illumos;
+pub(crate) mod irix;
 pub(crate) mod l4re;
 pub(crate) mod linux;
 pub(crate) mod linux_gnu;
