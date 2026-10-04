$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- vendor/libc-0.2.183/src/new/mod.rs.orig
+++ vendor/libc-0.2.183/src/new/mod.rs
@@ -44,6 +44,9 @@ cfg_if! {
     if #[cfg(target_os = "aix")] {
         mod aix;
         pub(crate) use aix::*;
+    } else if #[cfg(target_os = "irix")] {
+        mod irix;
+        pub(crate) use irix::*;
     } else if #[cfg(target_os = "android")] {
         mod bionic_libc;
         pub(crate) use bionic_libc::*;
