$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies IRIX builds use.

--- socket2-0.4.10/src/socket.rs.orig
+++ socket2-0.4.10/src/socket.rs
@@ -748,6 +748,7 @@ fn set_common_flags(socket: Socket) -> io::Result<Socket> {
 /// that an appropriate interface should be selected by the system.
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "redox",
@@ -1168,6 +1169,7 @@ impl Socket {
     /// group. See [`InterfaceIndexOrAddress`].
     #[cfg(not(any(
         target_os = "haiku",
+        target_os = "irix",
         target_os = "illumos",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1200,6 +1202,7 @@ impl Socket {
     /// [`join_multicast_v4_n`]: Socket::join_multicast_v4_n
     #[cfg(not(any(
         target_os = "haiku",
+        target_os = "irix",
         target_os = "illumos",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1235,6 +1238,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "netbsd",
         target_os = "openbsd",
         target_os = "redox",
@@ -1272,6 +1276,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "netbsd",
         target_os = "openbsd",
         target_os = "redox",
@@ -1446,6 +1451,7 @@ impl Socket {
     /// incoming packets. It contains a byte which specifies the
     /// Type of Service/Precedence field of the packet header.
     #[cfg(not(any(
+        target_os = "irix",
         target_os = "dragonfly",
         target_os = "fuchsia",
         target_os = "illumos",
@@ -1477,6 +1483,7 @@ impl Socket {
     ///
     /// [`set_recv_tos`]: Socket::set_recv_tos
     #[cfg(not(any(
+        target_os = "irix",
         target_os = "dragonfly",
         target_os = "fuchsia",
         target_os = "illumos",
@@ -1707,6 +1714,7 @@ impl Socket {
             not(any(
                 windows,
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "openbsd",
                 target_os = "vita"
             ))
@@ -1719,6 +1727,7 @@ impl Socket {
             not(any(
                 windows,
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "openbsd",
                 target_os = "vita"
             ))
