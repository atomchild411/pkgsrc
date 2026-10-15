$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/fs/dir.rs.orig
+++ rustix-1.1.5/src/backend/libc/fs/dir.rs
@@ -2,6 +2,7 @@
     solarish,
     target_os = "aix",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "vita"
 )))]
@@ -16,6 +17,7 @@ use crate::fs::{fstat, Stat};
 #[cfg(not(any(
     solarish,
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -203,6 +205,7 @@ impl Dir {
                         solarish,
                         target_os = "aix",
                         target_os = "haiku",
+                        target_os = "irix",
                         target_os = "nto",
                         target_os = "vita"
                     )))]
@@ -243,6 +246,7 @@ impl Dir {
     #[cfg(not(any(
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "netbsd",
         target_os = "nto",
@@ -321,6 +325,7 @@ pub struct DirEntry {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita"
     )))]
@@ -373,6 +378,7 @@ impl DirEntry {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita"
     )))]
