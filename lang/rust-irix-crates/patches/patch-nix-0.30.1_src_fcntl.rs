$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/fcntl.rs.orig
+++ nix-0.30.1/src/fcntl.rs
@@ -129,7 +129,8 @@
             solarish,
             target_os = "aix",
             target_os = "haiku",
-            target_os = "cygwin"
+            target_os = "cygwin",
+            target_os = "irix",
         )))]
         O_ASYNC;
         /// Closes the file descriptor once an `execve` call is made.
