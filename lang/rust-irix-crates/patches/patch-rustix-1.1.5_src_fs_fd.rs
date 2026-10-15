$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/fs/fd.rs.orig
+++ rustix-1.1.5/src/fs/fd.rs
@@ -32,6 +32,7 @@ use backend::fs::types::Stat;
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -170,6 +171,7 @@ pub fn fstat<Fd: AsFd>(fd: Fd) -> io::Result<Stat> {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -210,7 +212,7 @@ pub fn fstatvfs<Fd: AsFd>(fd: Fd) -> io::Result<StatVfs> {
 ///
 /// [POSIX]: https://pubs.opengroup.org/onlinepubs/9799919799/functions/futimens.html
 /// [Linux]: https://man7.org/linux/man-pages/man2/utimensat.2.html
-#[cfg(not(any(target_os = "espidf", target_os = "horizon", target_os = "vita")))]
+#[cfg(not(any(target_os = "irix", target_os = "espidf", target_os = "horizon", target_os = "vita")))]
 #[inline]
 pub fn futimens<Fd: AsFd>(fd: Fd, times: &Timestamps) -> io::Result<()> {
     backend::fs::syscalls::futimens(fd.as_fd(), times)
@@ -231,7 +233,7 @@ pub fn futimens<Fd: AsFd>(fd: Fd, times: &Timestamps) -> io::Result<()> {
 /// [POSIX]: https://pubs.opengroup.org/onlinepubs/9799919799/functions/posix_fallocate.html
 /// [Linux `fallocate`]: https://man7.org/linux/man-pages/man2/fallocate.2.html
 /// [Linux `posix_fallocate`]: https://man7.org/linux/man-pages/man3/posix_fallocate.3.html
-#[cfg(not(any(
+#[cfg(not(any(target_os = "irix", 
     netbsdlike,
     target_os = "dragonfly",
     target_os = "espidf",
@@ -278,6 +280,7 @@ pub fn fsync<Fd: AsFd>(fd: Fd) -> io::Result<()> {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita",
