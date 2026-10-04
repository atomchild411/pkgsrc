$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/os/mod.rs.orig
+++ library/std/src/os/mod.rs
@@ -123,6 +123,8 @@ pub mod windows;
 // Others.
 #[cfg(target_os = "aix")]
 pub mod aix;
+#[cfg(target_os = "irix")]
+pub mod irix;
 #[cfg(target_os = "android")]
 pub mod android;
 #[cfg(target_os = "cygwin")]
