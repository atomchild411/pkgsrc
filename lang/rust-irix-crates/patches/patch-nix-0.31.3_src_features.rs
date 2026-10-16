$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/features.rs.orig
+++ nix-0.31.3/src/features.rs
@@ -117,6 +117,7 @@
     apple_targets,
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "solaris"
 ))]
 mod os {
