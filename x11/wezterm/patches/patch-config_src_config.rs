$NetBSD$

IRIX has no RLIMIT_NPROC.

--- config/src/config.rs.orig
+++ config/src/config.rs
@@ -968,7 +968,7 @@
             }
         }
 
-        #[cfg(all(unix, not(target_os = "macos")))]
+        #[cfg(all(unix, not(any(target_os = "macos", target_os = "irix"))))]
         {
             use nix::sys::resource::{getrlimit, rlim_t, setrlimit, Resource};
             use std::convert::TryInto;
