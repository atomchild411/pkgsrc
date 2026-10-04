$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom, as on AIX; errno from __oserror.

--- getrandom-0.3.4/src/backends.rs.orig
+++ getrandom-0.3.4/src/backends.rs
@@ -59,6 +59,7 @@ cfg_if! {
         target_os = "redox",
         target_os = "nto",
         target_os = "aix",
+        target_os = "irix",
     ))] {
         mod use_file;
         pub use use_file::*;
