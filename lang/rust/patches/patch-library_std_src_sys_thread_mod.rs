$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/thread/mod.rs.orig
+++ library/std/src/sys/thread/mod.rs
@@ -58,6 +58,7 @@ cfg_select! {
             target_os = "redox",
             target_os = "hurd",
             target_os = "aix",
+            target_os = "irix",
             target_os = "wasi",
         )))]
         pub use unix::set_name;
@@ -84,6 +85,7 @@ cfg_select! {
             target_os = "redox",
             target_os = "hurd",
             target_os = "aix",
+            target_os = "irix",
             target_os = "wasi",
         ))]
         pub use unsupported::set_name;
