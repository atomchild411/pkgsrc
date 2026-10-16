$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/sys/ioctl/mod.rs.orig
+++ nix-0.30.1/src/sys/ioctl/mod.rs
@@ -234,11 +234,11 @@
 #[cfg(any(linux_android, target_os = "fuchsia", target_os = "redox"))]
 pub use self::linux::*;
 
-#[cfg(any(bsd, solarish, target_os = "haiku",))]
+#[cfg(any(bsd, solarish, target_os = "haiku", target_os = "irix"))]
 #[macro_use]
 mod bsd;
 
-#[cfg(any(bsd, solarish, target_os = "haiku",))]
+#[cfg(any(bsd, solarish, target_os = "haiku", target_os = "irix"))]
 pub use self::bsd::*;
 
 /// Convert raw ioctl return value to a Nix result
