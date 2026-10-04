$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/fd/unix.rs.orig
+++ library/std/src/sys/fd/unix.rs
@@ -562,6 +562,7 @@ impl FileDesc {
         target_os = "vxworks",
         target_os = "nto",
         target_os = "wasi",
+        target_os = "irix",
     )))]
     pub fn set_cloexec(&self) -> io::Result<()> {
         unsafe {
@@ -586,6 +587,7 @@ impl FileDesc {
         target_os = "vxworks",
         target_os = "nto",
         target_os = "wasi",
+        target_os = "irix",
     ))]
     pub fn set_cloexec(&self) -> io::Result<()> {
         unsafe {
