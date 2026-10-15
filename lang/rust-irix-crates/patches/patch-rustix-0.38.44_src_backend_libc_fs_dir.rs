$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/fs/dir.rs.orig
+++ rustix-0.38.44/src/backend/libc/fs/dir.rs
@@ -1,4 +1,4 @@
-#[cfg(not(any(solarish, target_os = "haiku", target_os = "nto", target_os = "vita")))]
+#[cfg(not(any(solarish, target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "vita")))]
 use super::types::FileType;
 use crate::backend::c;
 use crate::backend::conv::owned_fd;
@@ -10,6 +10,7 @@ use crate::fs::{fstat, Stat};
 #[cfg(not(any(
     solarish,
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -20,6 +21,7 @@ use crate::fs::{fstatfs, StatFs};
 #[cfg(not(any(
     solarish,
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
     target_os = "wasi"
@@ -163,6 +165,7 @@ impl Dir {
                         solarish,
                         target_os = "aix",
                         target_os = "haiku",
+                        target_os = "irix",
                         target_os = "nto",
                         target_os = "vita"
                     )))]
@@ -193,6 +196,7 @@ impl Dir {
     #[cfg(not(any(
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "netbsd",
         target_os = "nto",
         target_os = "redox",
@@ -208,6 +212,7 @@ impl Dir {
     #[cfg(not(any(
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "redox",
         target_os = "vita",
         target_os = "wasi"
@@ -266,6 +271,7 @@ pub struct DirEntry {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita"
     )))]
@@ -292,6 +298,7 @@ impl DirEntry {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita"
     )))]
