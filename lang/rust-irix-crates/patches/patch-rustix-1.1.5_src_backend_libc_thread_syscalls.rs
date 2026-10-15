$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/thread/syscalls.rs.orig
+++ rustix-1.1.5/src/backend/libc/thread/syscalls.rs
@@ -13,6 +13,7 @@ use crate::pid::Pid;
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "openbsd",
     target_os = "redox",
@@ -53,6 +54,7 @@ weak!(fn __nanosleep64(*const LibcTimespec, *mut LibcTimespec) -> c::c_int);
     target_os = "espidf",
     target_os = "freebsd", // FreeBSD 12 has clock_nanosleep, but libc targets FreeBSD 11.
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "openbsd",
     target_os = "redox",
@@ -116,6 +118,7 @@ pub(crate) fn clock_nanosleep_relative(id: ClockId, request: &Timespec) -> Nanos
         apple,
         target_os = "emscripten",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "vita"
     ))
@@ -164,6 +167,7 @@ fn clock_nanosleep_relative_old(
     target_os = "espidf",
     target_os = "freebsd", // FreeBSD 12 has clock_nanosleep, but libc targets FreeBSD 11.
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "openbsd",
     target_os = "redox",
@@ -220,6 +224,7 @@ pub(crate) fn clock_nanosleep_absolute(id: ClockId, request: &Timespec) -> io::R
         apple,
         target_os = "emscripten",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "vita"
     ))
