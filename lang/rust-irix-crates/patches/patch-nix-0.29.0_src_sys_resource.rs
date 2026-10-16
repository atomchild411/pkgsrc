$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/resource.rs.orig
+++ nix-0.29.0/src/sys/resource.rs
@@ -19,7 +19,8 @@
         bsd,
         target_os = "android",
         target_os = "aix",
-        all(target_os = "linux", not(target_env = "gnu"))
+        all(target_os = "linux", not(target_env = "gnu")),
+        target_os = "irix"
     ))]{
         use libc::rlimit;
     }
@@ -49,7 +50,8 @@
             bsd,
             target_os = "android",
             target_os = "aix",
-            all(target_os = "linux", not(any(target_env = "gnu", target_env = "uclibc")))
+            all(target_os = "linux", not(any(target_env = "gnu", target_env = "uclibc"))),
+            target_os = "irix"
         ), repr(i32))]
     #[non_exhaustive]
     pub enum Resource {
@@ -113,6 +115,7 @@
             target_os = "freebsd",
             netbsdlike,
             target_os = "aix",
+            target_os = "irix",
         ))]
         /// When there is memory pressure and swap is available, prioritize
         /// eviction of a process' resident pages beyond this amount (in bytes).
