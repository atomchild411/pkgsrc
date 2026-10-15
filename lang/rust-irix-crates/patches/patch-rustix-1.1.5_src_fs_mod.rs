$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/fs/mod.rs.orig
+++ rustix-1.1.5/src/fs/mod.rs
@@ -16,6 +16,7 @@ mod dir;
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "solaris",
@@ -39,6 +40,7 @@ mod ioctl;
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "vita",
     target_os = "wasi"
@@ -84,6 +86,7 @@ pub use dir::{Dir, DirEntry};
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "solaris",
@@ -105,6 +108,7 @@ pub use ioctl::*;
 #[cfg(not(any(
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "vita",
     target_os = "wasi"
