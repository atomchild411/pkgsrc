$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom, as on AIX; errno from __oserror. Cargo.toml: only the dependencies IRIX builds use.

--- getrandom-0.3.4/src/util_libc.rs.orig
+++ getrandom-0.3.4/src/util_libc.rs
@@ -22,6 +22,8 @@ cfg_if! {
         use __errno as errno_location;
     } else if #[cfg(target_os = "aix")] {
         use libc::_Errno as errno_location;
+    } else if #[cfg(target_os = "irix")] {
+        use libc::__oserror as errno_location;
     }
 }
 
