$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.5.10/src/sys/unix.rs.orig
+++ socket2-0.5.10/src/sys/unix.rs
@@ -137,6 +137,7 @@ pub(crate) use libc::ipv6_mreq as Ipv6Mreq;
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "espidf",
         target_os = "vita",
         target_os = "cygwin",
@@ -153,6 +154,7 @@ pub(crate) use libc::IPV6_RECVHOPLIMIT;
     target_os = "redox",
     target_os = "solaris",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "espidf",
     target_os = "vita",
 )))]
@@ -169,6 +171,7 @@ pub(crate) use libc::IP_HDRINCL;
     target_os = "redox",
     target_os = "solaris",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "nto",
     target_os = "espidf",
@@ -181,6 +184,7 @@ pub(crate) use libc::IP_RECVTOS;
     target_os = "redox",
     target_os = "solaris",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
 )))]
 pub(crate) use libc::IP_TOS;
@@ -212,6 +216,7 @@ pub(crate) use libc::{
 #[cfg(not(any(
     target_os = "dragonfly",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "netbsd",
     target_os = "openbsd",
@@ -228,6 +233,7 @@ pub(crate) use libc::{
     target_os = "dragonfly",
     target_os = "freebsd",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "ios",
     target_os = "visionos",
@@ -244,6 +250,7 @@ pub(crate) use libc::{IPV6_ADD_MEMBERSHIP, IPV6_DROP_MEMBERSHIP};
     target_os = "dragonfly",
     target_os = "freebsd",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "ios",
     target_os = "visionos",
@@ -291,6 +298,7 @@ pub(crate) type Bool = c_int;
 use libc::TCP_KEEPALIVE as KEEPALIVE_TIME;
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "ios",
     target_os = "visionos",
     target_os = "macos",
@@ -374,6 +382,7 @@ type IovLen = usize;
     target_os = "freebsd",
     target_os = "fuchsia",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "hurd",
     target_os = "illumos",
     target_os = "ios",
@@ -538,7 +547,7 @@ impl_debug!(
     libc::SOCK_DCCP,
     #[cfg(not(any(target_os = "redox", target_os = "espidf")))]
     libc::SOCK_RAW,
-    #[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "espidf")))]
+    #[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "irix", target_os = "espidf")))]
     libc::SOCK_RDM,
     #[cfg(not(target_os = "espidf"))]
     libc::SOCK_SEQPACKET,
@@ -1248,13 +1257,13 @@ fn into_timeval(duration: Option<Duration>) -> libc::timeval {
 
 #[cfg(all(
     feature = "all",
-    not(any(target_os = "haiku", target_os = "openbsd", target_os = "vita"))
+    not(any(target_os = "haiku", target_os = "irix", target_os = "openbsd", target_os = "vita"))
 ))]
 #[cfg_attr(
     docsrs,
     doc(cfg(all(
         feature = "all",
-        not(any(target_os = "haiku", target_os = "openbsd", target_os = "vita"))
+        not(any(target_os = "haiku", target_os = "irix", target_os = "openbsd", target_os = "vita"))
     )))
 )]
 pub(crate) fn keepalive_time(fd: Socket) -> io::Result<Duration> {
@@ -1268,6 +1277,7 @@ pub(crate) fn keepalive_time(fd: Socket) -> io::Result<Duration> {
 pub(crate) fn set_tcp_keepalive(fd: Socket, keepalive: &TcpKeepalive) -> io::Result<()> {
     #[cfg(not(any(
         target_os = "haiku",
+        target_os = "irix",
         target_os = "openbsd",
         target_os = "nto",
         target_os = "vita"
@@ -1316,6 +1326,7 @@ pub(crate) fn set_tcp_keepalive(fd: Socket, keepalive: &TcpKeepalive) -> io::Res
 
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "openbsd",
     target_os = "nto",
     target_os = "vita"
@@ -1418,6 +1429,7 @@ pub(crate) fn from_in6_addr(addr: in6_addr) -> Ipv6Addr {
 #[cfg(not(any(
     target_os = "aix",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "openbsd",
