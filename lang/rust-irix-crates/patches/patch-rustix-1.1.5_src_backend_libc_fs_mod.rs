$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/fs/mod.rs.orig
+++ rustix-1.1.5/src/backend/libc/fs/mod.rs
@@ -8,6 +8,7 @@ pub mod inotify;
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "vita",
     target_os = "wasi"
