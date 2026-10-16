$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/sys/socket/mod.rs.orig
+++ nix-0.30.1/src/sys/socket/mod.rs
@@ -45,6 +45,7 @@
     target_os = "hurd",
     target_os = "redox",
     target_os = "cygwin",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 pub use self::addr::{LinkAddr, SockaddrIn, SockaddrIn6};
@@ -54,6 +55,7 @@
     target_os = "hurd",
     target_os = "redox",
     target_os = "cygwin",
+    target_os = "irix",
 ))]
 #[cfg(feature = "net")]
 pub use self::addr::{SockaddrIn, SockaddrIn6};
@@ -1025,7 +1027,7 @@
                 let cred: libc::cmsgcred = unsafe { ptr::read_unaligned(p as *const _) };
                 ControlMessageOwned::ScmCreds(cred.into())
             }
-            #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "cygwin")))]
+            #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "cygwin", target_os = "irix")))]
             (libc::SOL_SOCKET, libc::SCM_TIMESTAMP) => {
                 let tv: libc::timeval = unsafe { ptr::read_unaligned(p as *const _) };
                 ControlMessageOwned::ScmTimestamp(TimeVal::from(tv))
@@ -1375,14 +1377,16 @@
     /// Safe because CMSG_LEN is always safe
     #[cfg(any(target_os = "android",
               all(target_os = "linux", not(any(target_env = "musl", target_env = "ohos"))),
-              target_os = "cygwin"))]
+              target_os = "cygwin",
+              target_os = "irix"))]
     fn cmsg_len(&self) -> usize {
         unsafe{CMSG_LEN(self.len() as libc::c_uint) as usize}
     }
 
     #[cfg(not(any(target_os = "android",
               all(target_os = "linux", not(any(target_env = "musl", target_env = "ohos"))),
-              target_os = "cygwin")))]
+              target_os = "cygwin",
+              target_os = "irix")))]
     fn cmsg_len(&self) -> libc::c_uint {
         unsafe{CMSG_LEN(self.len() as libc::c_uint)}
     }
