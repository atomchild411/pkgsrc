$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/net/addr.rs.orig
+++ rustix-0.38.44/src/backend/libc/net/addr.rs
@@ -80,7 +80,7 @@ impl SocketAddrUnix {
                 bsd,
                 target_os = "aix",
                 target_os = "haiku",
-                target_os = "nto",
+                                target_os = "nto",
                 target_os = "hurd",
             ))]
             sun_len: 0,
@@ -220,7 +220,7 @@ pub(crate) fn offsetof_sun_path() -> usize {
             bsd,
             target_os = "aix",
             target_os = "haiku",
-            target_os = "hurd",
+                        target_os = "hurd",
             target_os = "nto",
         ))]
         sun_len: 0_u8,
@@ -231,7 +231,7 @@ pub(crate) fn offsetof_sun_path() -> usize {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
-            target_os = "hurd",
+                        target_os = "hurd",
             target_os = "nto",
             target_os = "vita"
         ))]
