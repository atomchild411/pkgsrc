$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom; errno from __oserror() (as getrandom 0.2 here).

--- getrandom-0.1.16/src/lib.rs.orig
+++ getrandom-0.1.16/src/lib.rs
@@ -173,6 +173,7 @@
     target_os = "haiku",
     target_os = "illumos",
     target_os = "ios",
+    target_os = "irix",
     target_os = "linux",
     target_os = "macos",
     target_os = "netbsd",
@@ -206,6 +207,9 @@
     } else if #[cfg(target_os = "haiku")] {
         mod util_libc;
         #[path = "use_file.rs"] mod imp;
+    } else if #[cfg(target_os = "irix")] {
+        mod util_libc;
+        #[path = "use_file.rs"] mod imp;
     } else if #[cfg(target_os = "illumos")] {
         mod util_libc;
         mod use_file;
