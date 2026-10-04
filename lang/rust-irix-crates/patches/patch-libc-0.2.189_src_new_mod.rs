$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the target's module, IRIX as the IRIX toolchain (clang with its IRIX
header wrappers and builtins) sees it.

--- libc-0.2.189/src/new/mod.rs.orig
+++ libc-0.2.189/src/new/mod.rs
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
