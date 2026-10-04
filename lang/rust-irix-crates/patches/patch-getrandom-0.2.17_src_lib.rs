$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom, as on AIX; errno from __oserror.

--- getrandom-0.2.17/src/lib.rs.orig
+++ getrandom-0.2.17/src/lib.rs
@@ -235,7 +235,7 @@ pub use crate::error::Error;
 // The function MUST NOT ever write uninitialized bytes into `dest`,
 // regardless of what value it returns.
 cfg_if! {
-    if #[cfg(any(target_os = "haiku", target_os = "redox", target_os = "nto", target_os = "aix"))] {
+    if #[cfg(any(target_os = "haiku", target_os = "redox", target_os = "nto", target_os = "aix", target_os = "irix"))] {
         mod util_libc;
         #[path = "use_file.rs"] mod imp;
     } else if #[cfg(any(
