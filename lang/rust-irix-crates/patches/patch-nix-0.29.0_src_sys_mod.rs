$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/mod.rs.orig
+++ nix-0.29.0/src/sys/mod.rs
@@ -31,7 +31,7 @@
     pub mod fanotify;
 }
 
-#[cfg(any(bsd, linux_android, target_os = "redox", solarish))]
+#[cfg(any(bsd, linux_android, target_os = "redox", solarish, target_os = "irix"))]
 #[cfg(feature = "ioctl")]
 #[cfg_attr(docsrs, doc(cfg(feature = "ioctl")))]
 #[macro_use]
