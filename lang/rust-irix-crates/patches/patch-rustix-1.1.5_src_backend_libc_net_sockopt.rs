$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/net/sockopt.rs.orig
+++ rustix-1.1.5/src/backend/libc/net/sockopt.rs
@@ -27,6 +27,7 @@ use crate::net::xdp::{XdpMmapOffsets, XdpOptionsFlags, XdpRingOffset, XdpStatist
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -79,7 +80,7 @@ use alloc::borrow::ToOwned as _;
 use alloc::string::String;
 #[cfg(apple)]
 use c::TCP_KEEPALIVE as TCP_KEEPIDLE;
-#[cfg(not(any(apple, target_os = "haiku", target_os = "nto", target_os = "openbsd")))]
+#[cfg(not(any(apple, target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "openbsd")))]
 use c::TCP_KEEPIDLE;
 use core::mem::{size_of, MaybeUninit};
 use core::time::Duration;
@@ -391,6 +392,7 @@ pub(crate) fn socket_send_buffer_size(fd: BorrowedFd<'_>) -> io::Result<usize> {
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "hurd",
     target_os = "netbsd",
@@ -688,6 +690,7 @@ pub(crate) fn set_ipv6_add_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     )))]
@@ -696,6 +699,7 @@ pub(crate) fn set_ipv6_add_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     ))]
@@ -743,6 +747,7 @@ pub(crate) fn set_ipv6_drop_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     )))]
@@ -751,6 +756,7 @@ pub(crate) fn set_ipv6_drop_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     ))]
@@ -780,6 +786,7 @@ pub(crate) fn set_ipv6_unicast_hops(fd: BorrowedFd<'_>, hops: Option<u8>) -> io:
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -794,6 +801,7 @@ pub(crate) fn set_ip_tos(fd: BorrowedFd<'_>, value: u8) -> io::Result<()> {
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -902,6 +910,7 @@ pub(crate) fn ipv6_original_dst(fd: BorrowedFd<'_>) -> io::Result<SocketAddrV6>
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita"
@@ -916,6 +925,7 @@ pub(crate) fn set_ipv6_tclass(fd: BorrowedFd<'_>, value: u32) -> io::Result<()>
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita"
@@ -938,6 +948,7 @@ pub(crate) fn tcp_nodelay(fd: BorrowedFd<'_>) -> io::Result<bool> {
 #[inline]
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
@@ -949,6 +960,7 @@ pub(crate) fn set_tcp_keepcnt(fd: BorrowedFd<'_>, count: u32) -> io::Result<()>
 #[inline]
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
@@ -958,14 +970,14 @@ pub(crate) fn tcp_keepcnt(fd: BorrowedFd<'_>) -> io::Result<u32> {
 }
 
 #[inline]
-#[cfg(not(any(target_os = "haiku", target_os = "nto", target_os = "openbsd")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "openbsd")))]
 pub(crate) fn set_tcp_keepidle(fd: BorrowedFd<'_>, duration: Duration) -> io::Result<()> {
     let secs: c::c_uint = duration_to_secs(duration)?;
     setsockopt(fd, c::IPPROTO_TCP, TCP_KEEPIDLE, secs)
 }
 
 #[inline]
-#[cfg(not(any(target_os = "haiku", target_os = "nto", target_os = "openbsd")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "openbsd")))]
 pub(crate) fn tcp_keepidle(fd: BorrowedFd<'_>) -> io::Result<Duration> {
     let secs: c::c_uint = getsockopt(fd, c::IPPROTO_TCP, TCP_KEEPIDLE)?;
     Ok(Duration::from_secs(secs as u64))
@@ -974,6 +986,7 @@ pub(crate) fn tcp_keepidle(fd: BorrowedFd<'_>) -> io::Result<Duration> {
 #[inline]
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
@@ -986,6 +999,7 @@ pub(crate) fn set_tcp_keepintvl(fd: BorrowedFd<'_>, duration: Duration) -> io::R
 #[inline]
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
