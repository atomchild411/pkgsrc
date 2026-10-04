$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.6.5/src/lib.rs.orig
+++ socket2-0.6.5/src/lib.rs
@@ -191,6 +191,7 @@ use sys::c_int;
 pub use sockaddr::{sa_family_t, socklen_t, SockAddr, SockAddrStorage};
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "redox",
@@ -441,7 +442,7 @@ impl<'a> DerefMut for MaybeUninitSlice<'a> {
 #[derive(Debug, Clone)]
 pub struct TcpKeepalive {
     #[cfg_attr(
-        any(target_os = "openbsd", target_os = "haiku", target_os = "vita"),
+        any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "vita"),
         allow(dead_code)
     )]
     time: Option<Duration>,
@@ -453,6 +454,7 @@ pub struct TcpKeepalive {
         target_os = "espidf",
         target_os = "vita",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon"
     )))]
     interval: Option<Duration>,
@@ -464,6 +466,7 @@ pub struct TcpKeepalive {
         target_os = "espidf",
         target_os = "vita",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon"
     )))]
     retries: Option<u32>,
@@ -483,6 +486,7 @@ impl TcpKeepalive {
                 target_os = "espidf",
                 target_os = "vita",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "horizon"
             )))]
             interval: None,
@@ -494,6 +498,7 @@ impl TcpKeepalive {
                 target_os = "espidf",
                 target_os = "vita",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "horizon"
             )))]
             retries: None,
