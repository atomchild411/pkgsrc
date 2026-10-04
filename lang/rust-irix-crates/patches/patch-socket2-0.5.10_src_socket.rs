$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the options IRIX has (none of the BSD sockaddr lengths, IPv6 receive options or TCP keepalive tuning), as on Haiku. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- socket2-0.5.10/src/socket.rs.orig
+++ socket2-0.5.10/src/socket.rs
@@ -833,6 +833,7 @@ fn set_common_flags(socket: Socket) -> io::Result<Socket> {
 /// that an appropriate interface should be selected by the system.
 #[cfg(not(any(
     target_os = "haiku",
+    target_os = "irix",
     target_os = "illumos",
     target_os = "netbsd",
     target_os = "redox",
@@ -1314,6 +1315,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "illumos",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1348,6 +1350,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "illumos",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1384,6 +1387,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1422,6 +1426,7 @@ impl Socket {
     #[cfg(not(any(
         target_os = "dragonfly",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "netbsd",
         target_os = "openbsd",
@@ -1604,6 +1609,7 @@ impl Socket {
         target_os = "solaris",
         target_os = "illumos",
         target_os = "haiku",
+        target_os = "irix",
     )))]
     pub fn set_tos(&self, tos: u32) -> io::Result<()> {
         unsafe { setsockopt(self.as_raw(), sys::IPPROTO_IP, sys::IP_TOS, tos as c_int) }
@@ -1623,6 +1629,7 @@ impl Socket {
         target_os = "solaris",
         target_os = "illumos",
         target_os = "haiku",
+        target_os = "irix",
     )))]
     pub fn tos(&self) -> io::Result<u32> {
         unsafe {
@@ -1646,6 +1653,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "espidf",
         target_os = "vita",
@@ -1678,6 +1686,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "espidf",
         target_os = "vita",
@@ -1999,6 +2008,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "espidf",
         target_os = "vita",
@@ -2024,6 +2034,7 @@ impl Socket {
         target_os = "redox",
         target_os = "solaris",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "espidf",
         target_os = "vita",
@@ -2056,6 +2067,7 @@ impl Socket {
             target_os = "redox",
             target_os = "solaris",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "espidf",
             target_os = "vita",
@@ -2085,6 +2097,7 @@ impl Socket {
             target_os = "redox",
             target_os = "solaris",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "espidf",
             target_os = "vita",
@@ -2118,6 +2131,7 @@ impl Socket {
         not(any(
             windows,
             target_os = "haiku",
+            target_os = "irix",
             target_os = "openbsd",
             target_os = "vita"
         ))
@@ -2129,6 +2143,7 @@ impl Socket {
             not(any(
                 windows,
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "openbsd",
                 target_os = "vita"
             ))
