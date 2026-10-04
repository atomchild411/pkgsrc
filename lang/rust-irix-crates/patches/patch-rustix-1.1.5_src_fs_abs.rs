$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/fs/abs.rs.orig
+++ rustix-1.1.5/src/fs/abs.rs
@@ -7,6 +7,7 @@ use crate::fs::Access;
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -258,6 +259,7 @@ pub fn access<P: path::Arg>(path: P, access: Access) -> io::Result<()> {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
