$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku, and IP_TOS. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.6.5/src/socket.rs.orig
+++ socket2-0.6.5/src/socket.rs
@@ -850,6 +850,7 @@ fn set_common_accept_flags(socket: Socket) -> io::Result<Socket> {
 /// that an appropriate interface should be selected by the system.
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "redox",
@@ -1346,6 +1347,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "illumos",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1382,6 +1384,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "illumos",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1420,6 +1423,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1460,6 +1464,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1686,6 +1691,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "espidf",
         target_os = "nuttx",
@@ -1721,6 +1727,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "espidf",
         target_os = "nuttx",
@@ -2102,6 +2109,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "espidf",
         target_os = "nuttx",
@@ -2130,6 +2138,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "espidf",
         target_os = "nuttx",
@@ -2165,6 +2174,7 @@ impl Socket {
             target_os = "redox",
             target_os = "solaris",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "espidf",
             target_os = "vita",
@@ -2196,6 +2206,7 @@ impl Socket {
             target_os = "redox",
             target_os = "solaris",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "espidf",
             target_os = "vita",
@@ -2240,6 +2251,7 @@ impl Socket {
         not(any(
             windows,
             target_os = "haiku",
+            target_os = "irix",
             target_os = "openbsd",
             target_os = "vita"
         ))
