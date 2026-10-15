$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku, and IP_TOS. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.6.5/src/sys/unix.rs.orig
+++ socket2-0.6.5/src/sys/unix.rs
@@ -151,6 +151,7 @@ pub(crate) use libc::IPV6_HDRINCL;
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "espidf",
         target_os = "vita",
         target_os = "wasi",
@@ -169,6 +170,7 @@ pub(crate) use libc::IPV6_RECVHOPLIMIT;
     target_os = "redox",
     target_os = "solaris",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "espidf",
     target_os = "nuttx",
     target_os = "vita",
@@ -197,6 +199,7 @@ pub(crate) use libc::IP_HDRINCL;
     target_os = "redox",
     target_os = "solaris",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "nto",
     target_os = "espidf",
@@ -247,6 +250,7 @@ pub(crate) use libc::{
 #[cfg(not(any(
     target_os = "dragonfly",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "netbsd",
     target_os = "openbsd",
@@ -265,6 +269,7 @@ pub(crate) use libc::{
     target_os = "dragonfly",
     target_os = "freebsd",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "ios",
     target_os = "visionos",
@@ -283,6 +288,7 @@ pub(crate) use libc::{IPV6_ADD_MEMBERSHIP, IPV6_DROP_MEMBERSHIP};
     target_os = "dragonfly",
     target_os = "freebsd",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "ios",
     target_os = "visionos",
@@ -336,6 +342,7 @@ pub(crate) type Bool = c_int;
 use libc::TCP_KEEPALIVE as KEEPALIVE_TIME;
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "ios",
     target_os = "visionos",
     target_os = "macos",
@@ -420,6 +427,7 @@ type IovLen = usize;
     target_os = "freebsd",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "illumos",
     target_os = "ios",
@@ -548,6 +556,7 @@ impl_debug!(
     #[cfg(not(any(
         target_os = "redox",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "espidf",
         target_os = "wasi",
         target_os = "horizon"
@@ -1263,7 +1272,7 @@ fn into_timeval(duration: Option<Duration>) -> libc::timeval {
 
 #[cfg(all(
     feature = "all",
-    not(any(target_os = "haiku", target_os = "openbsd", target_os = "vita"))
+    not(any(target_os = "haiku", target_os = "irix", target_os = "openbsd", target_os = "vita"))
 ))]
 pub(crate) fn tcp_keepalive_time(fd: RawSocket) -> io::Result<Duration> {
     unsafe {
@@ -1276,6 +1285,7 @@ pub(crate) fn tcp_keepalive_time(fd: RawSocket) -> io::Result<Duration> {
 pub(crate) fn set_tcp_keepalive(fd: RawSocket, keepalive: &TcpKeepalive) -> io::Result<()> {
     #[cfg(not(any(
         target_os = "haiku",
+        target_os = "irix",
         target_os = "openbsd",
         target_os = "nto",
         target_os = "vita"
@@ -1327,6 +1337,7 @@ pub(crate) fn set_tcp_keepalive(fd: RawSocket, keepalive: &TcpKeepalive) -> io::
 
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "openbsd",
     target_os = "nto",
     target_os = "vita"
@@ -1429,6 +1440,7 @@ pub(crate) fn from_in6_addr(addr: in6_addr) -> Ipv6Addr {
 #[cfg(not(any(
     target_os = "aix",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "openbsd",
