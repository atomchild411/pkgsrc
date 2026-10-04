$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom, as on AIX; errno from __oserror.

--- getrandom-0.2.17/src/util_libc.rs.orig
+++ getrandom-0.2.17/src/util_libc.rs
@@ -29,6 +29,8 @@ cfg_if! {
         use __errno as errno_location;
     } else if #[cfg(target_os = "aix")] {
         use libc::_Errno as errno_location;
+    } else if #[cfg(target_os = "irix")] {
+        use libc::__oserror as errno_location;
     }
 }
 
