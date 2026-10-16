$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/features.rs.orig
+++ nix-0.29.0/src/features.rs
@@ -116,6 +116,7 @@
     apple_targets,
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "solaris"
 ))]
 mod os {
