$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/net/read_sockaddr.rs.orig
+++ rustix-0.38.44/src/backend/libc/net/read_sockaddr.rs
@@ -39,7 +39,7 @@ struct sockaddr_header {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
-        target_os = "nto",
+                target_os = "nto",
         target_os = "vita"
     )))]
     ss_family: u16,
@@ -59,7 +59,7 @@ unsafe fn read_ss_family(storage: *const c::sockaddr_storage) -> u16 {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
-            target_os = "hurd",
+                        target_os = "hurd",
             target_os = "nto",
             target_os = "vita"
         ))]
@@ -69,7 +69,7 @@ unsafe fn read_ss_family(storage: *const c::sockaddr_storage) -> u16 {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
-            target_os = "hurd",
+                        target_os = "hurd",
             target_os = "nto",
             target_os = "vita"
         ))]
