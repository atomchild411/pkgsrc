$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/fs/syscalls.rs.orig
+++ rustix-0.38.44/src/backend/libc/fs/syscalls.rs
@@ -21,6 +21,7 @@ use crate::fs::Access;
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
 )))]
@@ -46,6 +47,7 @@ use crate::fs::SealFlags;
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -64,7 +66,7 @@ use crate::fs::Timestamps;
 )))]
 use crate::fs::{Dev, FileType};
 use crate::fs::{Mode, OFlags, SeekFrom, Stat};
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 use crate::fs::{StatVfs, StatVfsMountFlags};
 use crate::io;
 #[cfg(all(target_env = "gnu", fix_y2038))]
@@ -247,6 +249,7 @@ pub(crate) fn openat(
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -262,7 +265,7 @@ pub(crate) fn statfs(filename: &CStr) -> io::Result<StatFs> {
     }
 }
 
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 #[inline]
 pub(crate) fn statvfs(filename: &CStr) -> io::Result<StatVfs> {
     unsafe {
@@ -1194,6 +1197,7 @@ pub(crate) fn copy_file_range(
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
 )))]
@@ -1463,6 +1467,7 @@ fn fstat_old(fd: BorrowedFd<'_>) -> io::Result<Stat> {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -1477,7 +1482,7 @@ pub(crate) fn fstatfs(fd: BorrowedFd<'_>) -> io::Result<StatFs> {
     }
 }
 
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 pub(crate) fn fstatvfs(fd: BorrowedFd<'_>) -> io::Result<StatVfs> {
     let mut statvfs = MaybeUninit::<c::statvfs>::uninit();
     unsafe {
@@ -1486,7 +1491,7 @@ pub(crate) fn fstatvfs(fd: BorrowedFd<'_>) -> io::Result<StatVfs> {
     }
 }
 
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 fn libc_statvfs_to_statvfs(from: c::statvfs) -> StatVfs {
     StatVfs {
         f_bsize: from.f_bsize as u64,
@@ -1506,7 +1511,7 @@ fn libc_statvfs_to_statvfs(from: c::statvfs) -> StatVfs {
     }
 }
 
-#[cfg(not(any(target_os = "espidf", target_os = "vita")))]
+#[cfg(not(any(target_os = "irix", target_os = "espidf", target_os = "vita")))]
 pub(crate) fn futimens(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()> {
     // Old 32-bit version: libc has `futimens` but it is not y2038 safe by
     // default. But there may be a `__futimens64` we can use.
@@ -1529,7 +1534,7 @@ pub(crate) fn futimens(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()>
 
     // Main version: libc is y2038 safe and has `futimens`. Or, the platform
     // is not y2038 safe and there's nothing practical we can do.
-    #[cfg(not(any(apple, fix_y2038)))]
+    #[cfg(not(any(target_os = "irix", apple, fix_y2038)))]
     unsafe {
         use crate::utils::as_ptr;
 
@@ -1573,7 +1578,7 @@ pub(crate) fn futimens(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()>
     }
 }
 
-#[cfg(all(fix_y2038, not(apple)))]
+#[cfg(all(fix_y2038, not(apple), not(target_os = "irix")))]
 fn futimens_old(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()> {
     let old_times = [
         c::timespec {
@@ -1605,7 +1610,7 @@ fn futimens_old(fd: BorrowedFd<'_>, times: &Timestamps) -> io::Result<()> {
     unsafe { ret(c::futimens(borrowed_fd(fd), old_times.as_ptr())) }
 }
 
-#[cfg(not(any(
+#[cfg(not(any(target_os = "irix", 
     apple,
     netbsdlike,
     target_os = "dragonfly",
@@ -1634,7 +1639,7 @@ pub(crate) fn fallocate(
         ))
     }
 
-    #[cfg(not(any(linux_kernel, target_os = "fuchsia")))]
+    #[cfg(not(any(target_os = "irix", linux_kernel, target_os = "fuchsia")))]
     {
         assert!(mode.is_empty());
         let err = unsafe { c::posix_fallocate(borrowed_fd(fd), offset, len) };
@@ -1689,6 +1694,7 @@ pub(crate) fn fsync(fd: BorrowedFd<'_>) -> io::Result<()> {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
 )))]
