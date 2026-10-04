$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.4.10/src/sys/unix.rs.orig
+++ socket2-0.4.10/src/sys/unix.rs
@@ -90,6 +90,7 @@ pub(crate) use libc::IP_HDRINCL;
     target_os = "redox",
     target_os = "solaris",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "nto",
     target_os = "espidf",
     target_os = "vita",
@@ -116,6 +117,7 @@ pub(crate) use libc::{
 #[cfg(not(any(
     target_os = "dragonfly",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "openbsd",
     target_os = "redox",
@@ -131,6 +133,7 @@ pub(crate) use libc::{
     target_os = "dragonfly",
     target_os = "freebsd",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "openbsd",
@@ -143,6 +146,7 @@ pub(crate) use libc::{IPV6_ADD_MEMBERSHIP, IPV6_DROP_MEMBERSHIP};
     target_os = "dragonfly",
     target_os = "freebsd",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "openbsd",
@@ -175,6 +179,7 @@ use libc::TCP_KEEPALIVE as KEEPALIVE_TIME;
 #[cfg(not(any(
     target_vendor = "apple",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "openbsd",
     target_os = "nto",
     target_os = "vita",
@@ -233,6 +238,7 @@ type IovLen = usize;
     target_os = "freebsd",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "openbsd",
@@ -381,7 +387,7 @@ impl_debug!(
     libc::SOCK_DGRAM,
     #[cfg(not(any(target_os = "redox", target_os = "espidf")))]
     libc::SOCK_RAW,
-    #[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "espidf")))]
+    #[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "irix", target_os = "espidf")))]
     libc::SOCK_RDM,
     #[cfg(not(target_os = "espidf"))]
     libc::SOCK_SEQPACKET,
@@ -940,7 +946,7 @@ fn into_timeval(duration: Option<Duration>) -> libc::timeval {
 }
 
 #[cfg(feature = "all")]
-#[cfg(not(any(target_os = "haiku", target_os = "openbsd", target_os = "vita")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "openbsd", target_os = "vita")))]
 pub(crate) fn keepalive_time(fd: Socket) -> io::Result<Duration> {
     unsafe {
         getsockopt::<c_int>(fd, IPPROTO_TCP, KEEPALIVE_TIME)
@@ -952,6 +958,7 @@ pub(crate) fn keepalive_time(fd: Socket) -> io::Result<Duration> {
 pub(crate) fn set_tcp_keepalive(fd: Socket, keepalive: &TcpKeepalive) -> io::Result<()> {
     #[cfg(not(any(
         target_os = "haiku",
+        target_os = "irix",
         target_os = "openbsd",
         target_os = "nto",
         target_os = "vita"
@@ -993,6 +1000,7 @@ pub(crate) fn set_tcp_keepalive(fd: Socket, keepalive: &TcpKeepalive) -> io::Res
 
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "openbsd",
     target_os = "nto",
     target_os = "vita"
@@ -1088,6 +1096,7 @@ pub(crate) fn from_in6_addr(addr: in6_addr) -> Ipv6Addr {
 
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "openbsd",
