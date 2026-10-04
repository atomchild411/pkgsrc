$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.5.10/src/lib.rs.orig
+++ socket2-0.5.10/src/lib.rs
@@ -189,6 +189,7 @@ pub use sockref::SockRef;
 
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "redox",
@@ -426,7 +427,7 @@ impl<'a> DerefMut for MaybeUninitSlice<'a> {
 #[derive(Debug, Clone)]
 pub struct TcpKeepalive {
     #[cfg_attr(
-        any(target_os = "openbsd", target_os = "haiku", target_os = "vita"),
+        any(target_os = "openbsd", target_os = "haiku", target_os = "irix", target_os = "vita"),
         allow(dead_code)
     )]
     time: Option<Duration>,
@@ -438,6 +439,7 @@ pub struct TcpKeepalive {
         target_os = "espidf",
         target_os = "vita",
         target_os = "haiku",
+        target_os = "irix",
     )))]
     interval: Option<Duration>,
     #[cfg(not(any(
@@ -449,6 +451,7 @@ pub struct TcpKeepalive {
         target_os = "espidf",
         target_os = "vita",
         target_os = "haiku",
+        target_os = "irix",
     )))]
     retries: Option<u32>,
 }
@@ -467,6 +470,7 @@ impl TcpKeepalive {
                 target_os = "espidf",
                 target_os = "vita",
                 target_os = "haiku",
+                target_os = "irix",
             )))]
             interval: None,
             #[cfg(not(any(
@@ -478,6 +482,7 @@ impl TcpKeepalive {
                 target_os = "espidf",
                 target_os = "vita",
                 target_os = "haiku",
+                target_os = "irix",
             )))]
             retries: None,
         }
