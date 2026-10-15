$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/io/syscalls.rs.orig
+++ rustix-1.1.5/src/backend/libc/io/syscalls.rs
@@ -97,6 +97,7 @@ pub(crate) fn writev(fd: BorrowedFd<'_>, bufs: &[IoSlice<'_>]) -> io::Result<usi
     target_os = "cygwin",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "nto",
     target_os = "redox",
@@ -128,6 +129,7 @@ pub(crate) fn preadv(
     target_os = "cygwin",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "horizon",
     target_os = "redox",
@@ -272,6 +274,7 @@ pub(crate) fn dup2(fd: BorrowedFd<'_>, new: &mut OwnedFd) -> io::Result<()> {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "nto",
     target_os = "redox",
@@ -293,6 +296,7 @@ pub(crate) fn dup3(fd: BorrowedFd<'_>, new: &mut OwnedFd, flags: DupFlags) -> io
     target_os = "android",
     target_os = "dragonfly",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
 ))]
 pub(crate) fn dup3(fd: BorrowedFd<'_>, new: &mut OwnedFd, _flags: DupFlags) -> io::Result<()> {
