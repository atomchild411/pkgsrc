$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom, as on AIX; errno from __oserror. Cargo.toml: only the dependencies IRIX builds use.

--- getrandom-0.4.3/src/backends.rs.orig
+++ getrandom-0.4.3/src/backends.rs
@@ -46,6 +46,7 @@ cfg_if! {
         target_os = "redox",
         target_os = "nto",
         target_os = "aix",
+        target_os = "irix",
     ))] {
         mod use_file;
         pub use use_file::*;
