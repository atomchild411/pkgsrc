$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/socket/addr.rs.orig
+++ nix-0.29.0/src/sys/socket/addr.rs
@@ -78,7 +78,7 @@
     #[cfg(linux_android)]
     Ax25 = libc::AF_AX25,
     /// IPX - Novell protocols
-    #[cfg(not(any(target_os = "aix", target_os = "redox")))]
+    #[cfg(not(any(target_os = "aix", target_os = "redox", target_os = "irix")))]
     Ipx = libc::AF_IPX,
     /// AppleTalk
     #[cfg(not(target_os = "redox"))]
@@ -164,6 +164,7 @@
         apple_targets,
         target_os = "hurd",
         target_os = "redox",
+        target_os = "irix",
     )))]
     Bluetooth = libc::AF_BLUETOOTH,
     /// IUCV (inter-user communication vehicle) z/VM protocol for
@@ -180,6 +181,7 @@
         target_os = "haiku",
         target_os = "hurd",
         target_os = "redox",
+        target_os = "irix",
     )))]
     Isdn = libc::AF_ISDN,
     /// Nokia cellular modem IPC/RPC interface
@@ -446,6 +448,7 @@
                      target_os = "fuchsia",
                      solarish,
                      target_os = "redox",
+                     target_os = "irix",
                 ))]
             {
                 UnixAddr { sun, sun_len }
@@ -510,6 +513,7 @@
                      target_os = "fuchsia",
                      solarish,
                      target_os = "redox",
+                     target_os = "irix",
                 ))]
             {
                 self.sun_len
@@ -526,7 +530,8 @@
         linux_android,
         target_os = "fuchsia",
         solarish,
-        target_os = "redox"
+        target_os = "redox",
+        target_os = "irix",
     ))]
     fn len(&self) -> libc::socklen_t {
         self.sun_len.into()
@@ -556,6 +561,7 @@
                          target_os = "fuchsia",
                          solarish,
                          target_os = "redox",
+                         target_os = "irix",
                 ))] {
                 let su_len = len.unwrap_or(
                     mem::size_of::<libc::sockaddr_un>() as libc::socklen_t
@@ -586,6 +592,7 @@
                          target_os = "fuchsia",
                          solarish,
                          target_os = "redox",
+                         target_os = "irix",
                 ))] {
                 self.sun_len = new_length as u8;
             }
@@ -1110,7 +1117,7 @@
     alg: AlgAddr,
     #[cfg(all(
         feature = "net",
-        not(any(target_os = "hurd", target_os = "redox"))
+        not(any(target_os = "hurd", target_os = "redox", target_os = "irix"))
     ))]
     #[cfg_attr(docsrs, doc(cfg(feature = "net")))]
     dl: LinkAddr,
@@ -1154,6 +1161,7 @@
                     linux_android,
                     target_os = "fuchsia",
                     solarish,
+                    target_os = "irix",
                 ))]
                 if i32::from(ss.ss_family) == libc::AF_UNIX {
                     // Safe because we UnixAddr is strictly smaller than
@@ -1210,7 +1218,7 @@
         }
     }
 
-    #[cfg(any(linux_android, target_os = "fuchsia", solarish))]
+    #[cfg(any(linux_android, target_os = "fuchsia", solarish, target_os = "irix"))]
     fn len(&self) -> libc::socklen_t {
         match self.as_unix_addr() {
             // The UnixAddr type knows its own length
@@ -1272,6 +1280,7 @@
             if #[cfg(any(linux_android,
                      target_os = "fuchsia",
                      solarish,
+                     target_os = "irix",
                 ))]
             {
                 let p = unsafe{ &self.ss as *const libc::sockaddr_storage };
@@ -1301,6 +1310,7 @@
             if #[cfg(any(linux_android,
                      target_os = "fuchsia",
                      solarish,
+                     target_os = "irix",
                 ))]
             {
                 let p = unsafe{ &self.ss as *const libc::sockaddr_storage };
