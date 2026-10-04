$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/net/write_sockaddr.rs.orig
+++ rustix-0.38.44/src/backend/libc/net/write_sockaddr.rs
@@ -32,7 +32,7 @@ pub(crate) fn encode_sockaddr_v4(v4: &SocketAddrV4) -> c::sockaddr_in {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
-            target_os = "hurd",
+                        target_os = "hurd",
             target_os = "nto",
             target_os = "vita",
         ))]
@@ -63,6 +63,7 @@ pub(crate) fn encode_sockaddr_v6(v6: &SocketAddrV6) -> c::sockaddr_in6 {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita"
@@ -82,6 +83,7 @@ pub(crate) fn encode_sockaddr_v6(v6: &SocketAddrV6) -> c::sockaddr_in6 {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita"
