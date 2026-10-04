$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies IRIX builds use.

--- socket2-0.4.10/src/lib.rs.orig
+++ socket2-0.4.10/src/lib.rs
@@ -134,6 +134,7 @@ pub use sockref::SockRef;
 
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "redox",
