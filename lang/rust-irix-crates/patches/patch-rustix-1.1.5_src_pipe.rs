$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/pipe.rs.orig
+++ rustix-1.1.5/src/pipe.rs
@@ -9,6 +9,7 @@ use crate::{backend, io};
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita",
@@ -37,6 +38,7 @@ pub use backend::pipe::types::{IoSliceRaw, SpliceFlags};
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "hurd",
     target_os = "redox",
@@ -103,6 +105,7 @@ pub fn pipe() -> io::Result<(OwnedFd, OwnedFd)> {
     target_os = "aix",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "nto"
 )))]
