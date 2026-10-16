$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/sys/mod.rs.orig
+++ nix-0.31.3/src/sys/mod.rs
@@ -41,6 +41,7 @@
     target_os = "fuchsia",
     target_os = "redox",
     target_os = "cygwin",
+    target_os = "irix",
 ))]
 #[cfg(feature = "ioctl")]
 #[cfg_attr(docsrs, doc(cfg(feature = "ioctl")))]
