$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom; errno from __oserror() (as getrandom 0.2 here).

--- getrandom-0.1.16/src/util_libc.rs.orig
+++ getrandom-0.1.16/src/util_libc.rs
@@ -23,6 +23,8 @@
         use libc::__error as errno_location;
     } else if #[cfg(target_os = "haiku")] {
         use libc::_errnop as errno_location;
+    } else if #[cfg(target_os = "irix")] {
+        use libc::__oserror as errno_location;
     }
 }
 
