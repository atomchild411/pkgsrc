$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/random/mod.rs.orig
+++ library/std/src/sys/random/mod.rs
@@ -18,6 +18,7 @@ cfg_select! {
         target_os = "freebsd",
         target_os = "haiku",
         target_os = "illumos",
+        target_os = "irix",
         target_os = "netbsd",
         target_os = "openbsd",
         target_os = "rtems",
