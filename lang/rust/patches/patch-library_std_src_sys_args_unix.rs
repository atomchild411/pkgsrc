$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/args/unix.rs.orig
+++ library/std/src/sys/args/unix.rs
@@ -80,6 +80,7 @@ pub fn args() -> Args {
     target_os = "vxworks",
     target_os = "horizon",
     target_os = "aix",
+    target_os = "irix",
     target_os = "nto",
     target_os = "hurd",
     target_os = "rtems",
