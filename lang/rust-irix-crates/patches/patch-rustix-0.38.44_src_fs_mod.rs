$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/fs/mod.rs.orig
+++ rustix-0.38.44/src/fs/mod.rs
@@ -17,6 +17,7 @@ mod dir;
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
 )))]
@@ -38,6 +39,7 @@ mod ioctl;
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
     target_os = "wasi"
@@ -86,6 +88,7 @@ pub use dir::{Dir, DirEntry};
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
 )))]
@@ -105,6 +108,7 @@ pub use ioctl::*;
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
     target_os = "wasi"
