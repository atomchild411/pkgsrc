$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/net/syscalls.rs.orig
+++ rustix-0.38.44/src/backend/libc/net/syscalls.rs
@@ -461,6 +461,7 @@ pub(crate) fn sendmsg_xdp(
     target_os = "aix",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "nto",
     target_os = "vita",
@@ -501,6 +502,7 @@ pub(crate) fn acceptfrom(sockfd: BorrowedFd<'_>) -> io::Result<(OwnedFd, Option<
     target_os = "aix",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "redox",
     target_os = "vita",
@@ -534,6 +536,7 @@ pub(crate) fn acceptfrom_with(
     target_os = "aix",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "vita",
 ))]
@@ -549,6 +552,7 @@ pub(crate) fn accept_with(sockfd: BorrowedFd<'_>, _flags: SocketFlags) -> io::Re
     target_os = "aix",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "vita",
 ))]
