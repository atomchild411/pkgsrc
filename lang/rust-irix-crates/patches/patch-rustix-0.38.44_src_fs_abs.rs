$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/fs/abs.rs.orig
+++ rustix-0.38.44/src/fs/abs.rs
@@ -7,6 +7,7 @@ use crate::fs::Access;
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -14,7 +15,7 @@ use crate::fs::Access;
     target_os = "wasi",
 )))]
 use crate::fs::StatFs;
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 use crate::fs::StatVfs;
 use crate::fs::{Mode, OFlags, Stat};
 #[cfg(not(target_os = "wasi"))]
@@ -256,6 +257,7 @@ pub fn access<P: path::Arg>(path: P, access: Access) -> io::Result<()> {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -280,7 +282,7 @@ pub fn statfs<P: path::Arg>(path: P) -> io::Result<StatFs> {
 ///
 /// [POSIX]: https://pubs.opengroup.org/onlinepubs/9799919799/functions/statvfs.html
 /// [Linux]: https://man7.org/linux/man-pages/man2/statvfs.2.html
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 #[inline]
 pub fn statvfs<P: path::Arg>(path: P) -> io::Result<StatVfs> {
     path.into_with_c_str(backend::fs::syscalls::statvfs)
