$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/sys/socket/addr.rs.orig
+++ nix-0.31.3/src/sys/socket/addr.rs
@@ -78,7 +78,7 @@
     #[cfg(linux_android)]
     Ax25 = libc::AF_AX25,
     /// IPX - Novell protocols
-    #[cfg(not(any(target_os = "aix", target_os = "redox", target_os = "cygwin")))]
+    #[cfg(not(any(target_os = "aix", target_os = "redox", target_os = "cygwin", target_os = "irix")))]
     Ipx = libc::AF_IPX,
     /// AppleTalk
     #[cfg(not(target_os = "redox"))]
@@ -165,6 +165,7 @@
         target_os = "hurd",
         target_os = "redox",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     Bluetooth = libc::AF_BLUETOOTH,
     /// IUCV (inter-user communication vehicle) z/VM protocol for
@@ -182,6 +183,7 @@
         target_os = "hurd",
         target_os = "redox",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     Isdn = libc::AF_ISDN,
     /// Nokia cellular modem IPC/RPC interface
@@ -449,6 +451,7 @@
                      solarish,
                      target_os = "redox",
                      target_os = "cygwin",
+                     target_os = "irix",
                 ))]
             {
                 UnixAddr { sun, sun_len }
@@ -514,6 +517,7 @@
                      solarish,
                      target_os = "redox",
                      target_os = "cygwin",
+                     target_os = "irix",
                 ))]
             {
                 self.sun_len
@@ -532,6 +536,7 @@
         solarish,
         target_os = "redox",
         target_os = "cygwin",
+        target_os = "irix",
     ))]
     fn len(&self) -> libc::socklen_t {
         self.sun_len.into()
@@ -562,6 +567,7 @@
                          solarish,
                          target_os = "redox",
                          target_os = "cygwin",
+                         target_os = "irix",
                 ))] {
                 let su_len = len.unwrap_or(
                     mem::size_of::<libc::sockaddr_un>() as libc::socklen_t
@@ -592,6 +598,7 @@
                          target_os = "fuchsia",
                          solarish,
                          target_os = "redox",
+                         target_os = "irix",
                 ))] {
                 self.sun_len = new_length as u8;
             }
@@ -1128,7 +1135,7 @@
     alg: AlgAddr,
     #[cfg(all(
         feature = "net",
-        not(any(target_os = "hurd", target_os = "redox", target_os = "cygwin"))
+        not(any(target_os = "hurd", target_os = "redox", target_os = "cygwin", target_os = "irix"))
     ))]
     #[cfg_attr(docsrs, doc(cfg(feature = "net")))]
     dl: LinkAddr,
@@ -1173,6 +1180,7 @@
                     target_os = "fuchsia",
                     solarish,
                     target_os = "cygwin",
+                    target_os = "irix",
                 ))]
                 if i32::from(ss.ss_family) == libc::AF_UNIX {
                     // Safe because we UnixAddr is strictly smaller than
@@ -1229,7 +1237,7 @@
         }
     }
 
-    #[cfg(any(linux_android, target_os = "fuchsia", solarish, target_os = "cygwin"))]
+    #[cfg(any(linux_android, target_os = "fuchsia", solarish, target_os = "cygwin", target_os = "irix"))]
     fn len(&self) -> libc::socklen_t {
         match self.as_unix_addr() {
             // The UnixAddr type knows its own length
@@ -1292,6 +1300,7 @@
                      target_os = "fuchsia",
                      solarish,
                      target_os = "cygwin",
+                     target_os = "irix",
                 ))]
             {
                 let p = unsafe{ &self.ss as *const libc::sockaddr_storage };
@@ -1322,6 +1331,7 @@
                      target_os = "fuchsia",
                      solarish,
                      target_os = "cygwin",
+                     target_os = "irix",
                 ))]
             {
                 let p = unsafe{ &self.ss as *const libc::sockaddr_storage };
