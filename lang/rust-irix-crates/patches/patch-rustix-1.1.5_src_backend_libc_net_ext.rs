$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/net/ext.rs.orig
+++ rustix-1.1.5/src/backend/libc/net/ext.rs
@@ -83,6 +83,7 @@ pub(crate) const fn sockaddr_in6_new(
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita"
@@ -100,7 +101,7 @@ pub(crate) const fn sockaddr_in6_new(
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
-            target_os = "hurd",
+                        target_os = "hurd",
             target_os = "nto",
             target_os = "vita"
         ))]
