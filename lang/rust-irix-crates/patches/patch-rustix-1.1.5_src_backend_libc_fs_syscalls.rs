$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/fs/syscalls.rs.orig
+++ rustix-1.1.5/src/backend/libc/fs/syscalls.rs
@@ -41,6 +41,7 @@ use crate::fs::SealFlags;
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -82,6 +83,7 @@ use {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "solaris",
@@ -256,6 +258,7 @@ pub(crate) fn openat(
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -1289,6 +1292,7 @@ pub(crate) fn copy_file_range(
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "solaris",
@@ -1604,6 +1608,7 @@ fn fstat_old(fd: BorrowedFd<'_>) -> io::Result<Stat> {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -1648,7 +1653,7 @@ fn libc_statvfs_to_statvfs(from: c::statvfs) -> StatVfs {
     }
 }
 
-#[cfg(not(any(target_os = "espidf", target_os = "horizon", target_os = "vita")))]
+#[cfg(not(any(target_os = "irix", target_os = "espidf", target_os = "horizon", target_os = "vita")))]
 pub(crate) fn futimens(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()> {
     // Old 32-bit version: libc has `futimens` but it is not y2038 safe by
     // default. But there may be a `__futimens64` we can use.
@@ -1669,7 +1674,7 @@ pub(crate) fn futimens(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()>
 
     // Main version: libc is y2038 safe and has `futimens`. Or, the platform
     // is not y2038 safe and there's nothing practical we can do.
-    #[cfg(not(any(apple, fix_y2038)))]
+    #[cfg(not(any(target_os = "irix", apple, fix_y2038)))]
     unsafe {
         use crate::utils::as_ptr;
 
@@ -1713,7 +1718,7 @@ pub(crate) fn futimens(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()>
     }
 }
 
-#[cfg(all(fix_y2038, not(apple)))]
+#[cfg(all(fix_y2038, not(apple), not(target_os = "irix")))]
 fn futimens_old(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()> {
     let old_times = [
         c::timespec {
@@ -1745,7 +1750,7 @@ fn futimens_old(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()> {
     unsafe { ret(c::futimens(borrowed_fd(fd), old_times.as_ptr())) }
 }
 
-#[cfg(not(any(
+#[cfg(not(any(target_os = "irix", 
     apple,
     netbsdlike,
     target_os = "dragonfly",
@@ -1779,7 +1784,7 @@ pub(crate) fn fallocate(
         ))
     }
 
-    #[cfg(not(any(linux_kernel, target_os = "fuchsia")))]
+    #[cfg(not(any(target_os = "irix", linux_kernel, target_os = "fuchsia")))]
     {
         assert!(mode.is_empty());
         let err = unsafe { c::posix_fallocate(borrowed_fd(fd), offset, len) };
@@ -1834,6 +1839,7 @@ pub(crate) fn fsync(fd: BorrowedFd<'_>) -> io::Result<()> {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita",
