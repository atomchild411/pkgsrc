$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/net/sockopt.rs.orig
+++ rustix-1.1.5/src/net/sockopt.rs
@@ -156,6 +156,7 @@ use crate::net::xdp::{XdpMmapOffsets, XdpOptionsFlags, XdpStatistics, XdpUmemReg
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -577,6 +578,7 @@ pub fn socket_send_buffer_size<Fd: AsFd>(fd: Fd) -> io::Result<usize> {
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "hurd",
     target_os = "netbsd",
@@ -1211,6 +1213,7 @@ pub fn set_ipv6_drop_membership<Fd: AsFd>(
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -1231,6 +1234,7 @@ pub fn set_ip_tos<Fd: AsFd>(fd: Fd, value: u8) -> io::Result<()> {
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -1400,6 +1404,7 @@ pub fn ipv6_original_dst<Fd: AsFd>(fd: Fd) -> io::Result<SocketAddrV6> {
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita"
@@ -1420,6 +1425,7 @@ pub fn set_ipv6_tclass<Fd: AsFd>(fd: Fd, value: u32) -> io::Result<()> {
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "redox",
     target_os = "vita"
@@ -1459,6 +1465,7 @@ pub fn tcp_nodelay<Fd: AsFd>(fd: Fd) -> io::Result<bool> {
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
@@ -1476,6 +1483,7 @@ pub fn set_tcp_keepcnt<Fd: AsFd>(fd: Fd, value: u32) -> io::Result<()> {
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
@@ -1493,7 +1501,7 @@ pub fn tcp_keepcnt<Fd: AsFd>(fd: Fd) -> io::Result<u32> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "haiku", target_os = "nto", target_os = "openbsd")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "openbsd")))]
 #[inline]
 #[doc(alias = "TCP_KEEPIDLE")]
 pub fn set_tcp_keepidle<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
@@ -1507,7 +1515,7 @@ pub fn set_tcp_keepidle<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "haiku", target_os = "nto", target_os = "openbsd")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "nto", target_os = "openbsd")))]
 #[inline]
 #[doc(alias = "TCP_KEEPIDLE")]
 pub fn tcp_keepidle<Fd: AsFd>(fd: Fd) -> io::Result<Duration> {
@@ -1521,6 +1529,7 @@ pub fn tcp_keepidle<Fd: AsFd>(fd: Fd) -> io::Result<Duration> {
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
@@ -1538,6 +1547,7 @@ pub fn set_tcp_keepintvl<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "openbsd",
     target_os = "redox"
