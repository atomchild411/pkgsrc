$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/net/sockopt.rs.orig
+++ rustix-0.38.44/src/net/sockopt.rs
@@ -153,6 +153,7 @@ use crate::net::xdp::{XdpMmapOffsets, XdpOptionsFlags, XdpStatistics, XdpUmemReg
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "vita",
@@ -454,6 +455,7 @@ pub fn get_socket_send_buffer_size<Fd: AsFd>(fd: Fd) -> io::Result<usize> {
     target_os = "emscripten",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "netbsd",
     target_os = "nto",
@@ -943,6 +945,7 @@ pub fn set_ipv6_drop_membership<Fd: AsFd>(
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -963,6 +966,7 @@ pub fn set_ip_tos<Fd: AsFd>(fd: Fd, value: u8) -> io::Result<()> {
     target_os = "aix",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_env = "newlib"
 ))]
@@ -1120,6 +1124,7 @@ pub fn get_ipv6_original_dst<Fd: AsFd>(fd: Fd) -> io::Result<SocketAddrV6> {
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "vita"
 )))]
 #[inline]
@@ -1138,6 +1143,7 @@ pub fn set_ipv6_tclass<Fd: AsFd>(fd: Fd, value: u32) -> io::Result<()> {
     windows,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "vita"
 )))]
 #[inline]
@@ -1173,7 +1179,7 @@ pub fn get_tcp_nodelay<Fd: AsFd>(fd: Fd) -> io::Result<bool> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 #[inline]
 #[doc(alias = "TCP_KEEPCNT")]
 pub fn set_tcp_keepcnt<Fd: AsFd>(fd: Fd, value: u32) -> io::Result<()> {
@@ -1185,7 +1191,7 @@ pub fn set_tcp_keepcnt<Fd: AsFd>(fd: Fd, value: u32) -> io::Result<()> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 #[inline]
 #[doc(alias = "TCP_KEEPCNT")]
 pub fn get_tcp_keepcnt<Fd: AsFd>(fd: Fd) -> io::Result<u32> {
@@ -1199,7 +1205,7 @@ pub fn get_tcp_keepcnt<Fd: AsFd>(fd: Fd) -> io::Result<u32> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 #[inline]
 #[doc(alias = "TCP_KEEPIDLE")]
 pub fn set_tcp_keepidle<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
@@ -1213,7 +1219,7 @@ pub fn set_tcp_keepidle<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 #[inline]
 #[doc(alias = "TCP_KEEPIDLE")]
 pub fn get_tcp_keepidle<Fd: AsFd>(fd: Fd) -> io::Result<Duration> {
@@ -1225,7 +1231,7 @@ pub fn get_tcp_keepidle<Fd: AsFd>(fd: Fd) -> io::Result<Duration> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 #[inline]
 #[doc(alias = "TCP_KEEPINTVL")]
 pub fn set_tcp_keepintvl<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
@@ -1237,7 +1243,7 @@ pub fn set_tcp_keepintvl<Fd: AsFd>(fd: Fd, value: Duration) -> io::Result<()> {
 /// See the [module-level documentation] for more.
 ///
 /// [module-level documentation]: self#references-for-get_tcp_-and-set_tcp_-functions
-#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "nto")))]
+#[cfg(not(any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "nto")))]
 #[inline]
 #[doc(alias = "TCP_KEEPINTVL")]
 pub fn get_tcp_keepintvl<Fd: AsFd>(fd: Fd) -> io::Result<Duration> {
