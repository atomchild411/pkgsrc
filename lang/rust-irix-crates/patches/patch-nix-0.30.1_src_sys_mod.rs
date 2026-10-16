$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/sys/mod.rs.orig
+++ nix-0.30.1/src/sys/mod.rs
@@ -40,6 +40,7 @@
     solarish,
     target_os = "fuchsia",
     target_os = "redox",
+    target_os = "irix",
 ))]
 #[cfg(feature = "ioctl")]
 #[cfg_attr(docsrs, doc(cfg(feature = "ioctl")))]
