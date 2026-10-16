$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/sys/socket/sockopt.rs.orig
+++ nix-0.31.3/src/sys/socket/sockopt.rs
@@ -739,7 +739,8 @@
 #[cfg(not(any(
     target_os = "openbsd",
     target_os = "haiku",
-    target_os = "redox"
+    target_os = "redox",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 sockopt_impl!(
@@ -765,7 +766,8 @@
 #[cfg(not(any(
     target_os = "openbsd",
     target_os = "haiku",
-    target_os = "redox"
+    target_os = "redox",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 sockopt_impl!(
@@ -912,7 +914,8 @@
     target_os = "haiku",
     target_os = "hurd",
     target_os = "redox",
-    target_os = "cygwin"
+    target_os = "cygwin",
+    target_os = "irix",
 )))]
 sockopt_impl!(
     /// Enable or disable the receiving of the `SO_TIMESTAMP` control message.
