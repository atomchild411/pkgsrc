$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/pal/unix/sync/condvar.rs.orig
+++ library/std/src/sys/pal/unix/sync/condvar.rs
@@ -139,6 +139,7 @@ impl Condvar {
     target_vendor = "apple",
     target_os = "espidf",
     target_os = "horizon",
+    target_os = "irix",
     target_os = "l4re",
     target_os = "redox",
     target_os = "teeos",
@@ -194,6 +195,7 @@ impl Condvar {
     target_os = "android",
     target_os = "espidf",
     target_os = "horizon",
+    target_os = "irix",
     target_os = "l4re",
     target_os = "redox",
     target_os = "teeos",
