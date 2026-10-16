$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/sys/socket/sockopt.rs.orig
+++ nix-0.30.1/src/sys/socket/sockopt.rs
@@ -738,7 +738,8 @@
 #[cfg(not(any(
     target_os = "openbsd",
     target_os = "haiku",
-    target_os = "redox"
+    target_os = "redox",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 sockopt_impl!(
@@ -764,7 +765,8 @@
 #[cfg(not(any(
     target_os = "openbsd",
     target_os = "haiku",
-    target_os = "redox"
+    target_os = "redox",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 sockopt_impl!(
@@ -911,7 +913,8 @@
     target_os = "haiku",
     target_os = "hurd",
     target_os = "redox",
-    target_os = "cygwin"
+    target_os = "cygwin",
+    target_os = "irix",
 )))]
 sockopt_impl!(
     /// Enable or disable the receiving of the `SO_TIMESTAMP` control message.
