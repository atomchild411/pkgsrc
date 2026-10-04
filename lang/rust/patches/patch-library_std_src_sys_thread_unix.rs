$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/thread/unix.rs.orig
+++ library/std/src/sys/thread/unix.rs
@@ -5,6 +5,7 @@
     target_os = "redox",
     target_os = "hurd",
     target_os = "aix",
+    target_os = "irix",
     target_os = "wasi",
 )))]
 use crate::ffi::CStr;
@@ -153,6 +154,7 @@ pub fn available_parallelism() -> io::Result<NonZero<usize>> {
             target_os = "hurd",
             target_os = "linux",
             target_os = "aix",
+            target_os = "irix",
             target_vendor = "apple",
             target_os = "cygwin",
         ) => {
