$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/net/sockopt.rs.orig
+++ rustix-0.38.44/src/backend/libc/net/sockopt.rs
@@ -24,6 +24,7 @@ use crate::net::xdp::{XdpMmapOffsets, XdpOptionsFlags, XdpRingOffset, XdpStatist
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "vita",
@@ -71,7 +72,7 @@ use alloc::borrow::ToOwned;
 use alloc::string::String;
 #[cfg(apple)]
 use c::TCP_KEEPALIVE as TCP_KEEPIDLE;
-#[cfg(not(any(apple, target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(apple, target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 use c::TCP_KEEPIDLE;
 use core::mem::{size_of, MaybeUninit};
 use core::time::Duration;
@@ -376,6 +377,7 @@ pub(crate) fn get_socket_send_buffer_size(fd: BorrowedFd<'_>) -> io::Result<usiz
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "netbsd",
     target_os = "nto",
@@ -592,6 +594,7 @@ pub(crate) fn set_ipv6_add_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     )))]
@@ -600,6 +603,7 @@ pub(crate) fn set_ipv6_add_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     ))]
@@ -647,6 +651,7 @@ pub(crate) fn set_ipv6_drop_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     )))]
@@ -655,6 +660,7 @@ pub(crate) fn set_ipv6_drop_membership(
         bsd,
         solarish,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "l4re",
         target_os = "nto"
     ))]
@@ -684,6 +690,7 @@ pub(crate) fn set_ipv6_unicast_hops(fd: BorrowedFd<'_>, hops: Option<u8>) -> io:
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -698,6 +705,7 @@ pub(crate) fn set_ip_tos(fd: BorrowedFd<'_>, value: u8) -> io::Result<()> {
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -806,6 +814,7 @@ pub(crate) fn get_ipv6_original_dst(fd: BorrowedFd<'_>) -> io::Result<SocketAddr
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "vita"
 )))]
 #[inline]
@@ -818,6 +827,7 @@ pub(crate) fn set_ipv6_tclass(fd: BorrowedFd<'_>, value: u32) -> io::Result<()>
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "vita"
 )))]
 #[inline]
@@ -836,40 +846,40 @@ pub(crate) fn get_tcp_nodelay(fd: BorrowedFd<'_>) -> io::Result<bool> {
 }
 
 #[inline]
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 pub(crate) fn set_tcp_keepcnt(fd: BorrowedFd<'_>, count: u32) -> io::Result<()> {
     setsockopt(fd, c::IPPROTO_TCP, c::TCP_KEEPCNT, count)
 }
 
 #[inline]
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 pub(crate) fn get_tcp_keepcnt(fd: BorrowedFd<'_>) -> io::Result<u32> {
     getsockopt(fd, c::IPPROTO_TCP, c::TCP_KEEPCNT)
 }
 
 #[inline]
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 pub(crate) fn set_tcp_keepidle(fd: BorrowedFd<'_>, duration: Duration) -> io::Result<()> {
     let secs: c::c_uint = duration_to_secs(duration)?;
     setsockopt(fd, c::IPPROTO_TCP, TCP_KEEPIDLE, secs)
 }
 
 #[inline]
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 pub(crate) fn get_tcp_keepidle(fd: BorrowedFd<'_>) -> io::Result<Duration> {
     let secs: c::c_uint = getsockopt(fd, c::IPPROTO_TCP, TCP_KEEPIDLE)?;
     Ok(Duration::from_secs(secs as u64))
 }
 
 #[inline]
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 pub(crate) fn set_tcp_keepintvl(fd: BorrowedFd<'_>, duration: Duration) -> io::Result<()> {
     let secs: c::c_uint = duration_to_secs(duration)?;
     setsockopt(fd, c::IPPROTO_TCP, c::TCP_KEEPINTVL, secs)
 }
 
 #[inline]
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 pub(crate) fn get_tcp_keepintvl(fd: BorrowedFd<'_>) -> io::Result<Duration> {
     let secs: c::c_uint = getsockopt(fd, c::IPPROTO_TCP, c::TCP_KEEPINTVL)?;
     Ok(Duration::from_secs(secs as u64))
