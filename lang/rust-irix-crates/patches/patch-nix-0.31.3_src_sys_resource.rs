$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/sys/resource.rs.orig
+++ nix-0.31.3/src/sys/resource.rs
@@ -21,7 +21,8 @@
         target_os = "aix",
         target_os = "illumos",
         all(target_os = "linux", not(target_env = "gnu")),
-        target_os = "cygwin"
+        target_os = "cygwin",
+        target_os = "irix"
     ))]{
         use libc::rlimit;
     }
@@ -53,7 +54,8 @@
             target_os = "aix",
             target_os = "illumos",
             all(target_os = "linux", not(any(target_env = "gnu", target_env = "uclibc"))),
-            target_os = "cygwin"
+            target_os = "cygwin",
+            target_os = "irix"
         ), repr(i32))]
     #[non_exhaustive]
     pub enum Resource {
@@ -117,6 +119,7 @@
             target_os = "freebsd",
             netbsdlike,
             target_os = "aix",
+            target_os = "irix",
         ))]
         /// When there is memory pressure and swap is available, prioritize
         /// eviction of a process' resident pages beyond this amount (in bytes).
