$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/fcntl.rs.orig
+++ nix-0.29.0/src/fcntl.rs
@@ -94,7 +94,8 @@
         #[cfg(not(any(
             solarish,
             target_os = "aix",
-            target_os = "haiku"
+            target_os = "haiku",
+            target_os = "irix",
         )))]
         O_ASYNC;
         /// Closes the file descriptor once an `execve` call is made.
