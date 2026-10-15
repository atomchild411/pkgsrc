$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/termios/mod.rs.orig
+++ rustix-1.1.5/src/termios/mod.rs
@@ -13,6 +13,7 @@
     target_os = "cygwin",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "wasi",
 )))]
 mod ioctl;
@@ -27,6 +28,7 @@ mod types;
     target_os = "cygwin",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "wasi",
 )))]
 pub use ioctl::*;
