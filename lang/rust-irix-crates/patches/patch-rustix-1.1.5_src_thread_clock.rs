$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/thread/clock.rs.orig
+++ rustix-1.1.5/src/thread/clock.rs
@@ -34,6 +34,7 @@ pub use crate::clockid::ClockId;
     target_os = "espidf",
     target_os = "freebsd", // FreeBSD 12 has clock_nanosleep, but libc targets FreeBSD 11.
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "openbsd",
     target_os = "redox",
@@ -64,6 +65,7 @@ pub fn clock_nanosleep_relative(id: ClockId, request: &Timespec) -> NanosleepRel
     target_os = "espidf",
     target_os = "freebsd", // FreeBSD 12 has clock_nanosleep, but libc targets FreeBSD 11.
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "openbsd",
     target_os = "redox",
