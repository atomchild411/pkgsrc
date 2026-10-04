$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/io/syscalls.rs.orig
+++ rustix-0.38.44/src/backend/libc/io/syscalls.rs
@@ -96,6 +96,7 @@ pub(crate) fn writev(fd: BorrowedFd<'_>, bufs: &[IoSlice<'_>]) -> io::Result<usi
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "nto",
     target_os = "redox",
@@ -122,6 +123,7 @@ pub(crate) fn preadv(
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "horizon",
     target_os = "redox",
@@ -316,6 +318,7 @@ pub(crate) fn dup2(fd: BorrowedFd<'_>, new: &mut OwnedFd) -> io::Result<()> {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "nto",
     target_os = "redox",
@@ -337,6 +340,7 @@ pub(crate) fn dup3(fd: BorrowedFd<'_>, new: &mut OwnedFd, flags: DupFlags) -> io
     target_os = "android",
     target_os = "dragonfly",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
 ))]
 pub(crate) fn dup3(fd: BorrowedFd<'_>, new: &mut OwnedFd, _flags: DupFlags) -> io::Result<()> {
